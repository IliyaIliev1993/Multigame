#include "MainGame.h"

#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <main_app/applications/roulette/math_logic/RouletteMathLogic.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerHoldWins = 1;
constexpr unsigned int g_unTimerHoldWinsPeriod = 1000;
constexpr unsigned int g_unDurationHoldWins = 7;

constexpr unsigned int g_unTimerHoldLoses = 2;
constexpr unsigned int g_unTimerHoldLosesPeriod = 1000;
constexpr unsigned int g_unDurationHoldLoses = 3;

Roulette::Roulette()
{
}

bool Roulette::Init()
{

    /*Load textures*/
    m_textureBackground = Texture::CreateTexture("../src/resources/roulette/background.png");

    if (!m_textureBackground->Load())
    {
        LOG_ERROR("Roulette - Unable to load texture background !");
        return false;
    }

    /*Initialize Math Logic*/
    if (!RouletteMathLogic::GetInstance().Init())
    {
        LOG_ERROR("Roulette - Unable to init math logic !");
        return false;
    }

    /*Initialize table area*/
    if (!m_tableArea.Init())
    {
        LOG_ERROR("Roulette - Unable to init table area !");
        return false;
    }

    /*Initialize wheel area*/
    if (!m_wheelArea.Init())
    {
        LOG_ERROR("Roulette - Unable to init wheel area !");
        return false;
    }

    /*Set callback when finished spinning, invoke it*/
    std::function<void()> afterSpinningStoppedCallback = [this]()
    {
        AfterSpinningStopped();
    };
    m_wheelArea.SetAfterSpinningStoppedCallback(afterSpinningStoppedCallback);

    LOG_INFO("Roulette - Initialized ...");
    return true;
}

bool Roulette::Deinit()
{
    /*Deinit wheel area*/
    m_wheelArea.Deinit();

    /*Deinit table area*/
    m_tableArea.Deinit();

    /*Deinitialize math logic*/
    RouletteMathLogic::GetInstance().Deinit();

    LOG_WARN("Roulette - Deinitalized ...");
    return true;
}

bool Roulette::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;

    /*ENTER button*/
    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter), false))
    {
        LOG_INFO("Roulette - ENTER Button Pressed");
        StartNewGame();
        return true;
    }

    /*Table Area Handle Event*/
    m_tableArea.HandleEvent();

    /*Wheel Area Handle Event*/
    m_wheelArea.HandleEvent();

    /*Panel Handle Event*/
    MainApp::GetInstance().ptrPanel->HandleEvent();

    return false;
}

const std::string &Roulette::GetAppName()
{
    return m_strAppName;
}

void Roulette::StartNewGame()
{
    m_wheelArea.StartNewSpin();
}

void ::Roulette::AfterSpinningStopped()
{
    const auto &unWinFromGame = RouletteMathLogic::GetInstance().GetTotalWinFromGame();
    /*If there is a win, start holding timer*/
    if (unWinFromGame != 0)
    {
        MainApp::GetInstance().ptrPanel->StartWinCounting(unWinFromGame);
        MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerHoldWins, g_unTimerHoldWinsPeriod);
    }
    else /*If there is NO win, reset game elements after timer expires*/
    {
        MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerHoldLoses, g_unTimerHoldLosesPeriod);
    }

    m_tableArea.StartWinAnimations();
    LOG_INFO("Roulette - Start Hold Timer");
}

void Roulette::OnEnter()
{
    MainApp::GetInstance().ptrPanel->LockBetButtons();
    LOG_INFO("Roulette - Transition to Application succeed");
}

void Roulette::OnExit()
{
    LOG_INFO("Roulette - Exit from Application");
    m_wheelArea.StopRotation();
}

void Roulette::OnDraw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Background*/
    rend->DrawPicture(m_textureBackground, 0.0f, 0.0f);

    /*Table Area Draw*/
    m_tableArea.Draw();

    /*Wheel Area Draw*/
    m_wheelArea.Draw();

    /*Draw Panel*/
    MainApp::GetInstance().ptrPanel->OnDraw();
}

void Roulette::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerHoldWins)
    {
        if (unTimes >= g_unDurationHoldWins && m_tableArea.IsEndGameScenarioFinished())
        {
            MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerHoldWins);
            ResetGameElements();
        }
    }

    if (unID == g_unTimerHoldLoses)
    {
        if (unTimes >= g_unDurationHoldLoses && m_tableArea.IsEndGameScenarioFinished())
        {
            MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerHoldLoses);
            ResetGameElements();
        }
    }
}

void Roulette::ResetGameElements()
{
    const auto &unWinFromGame = RouletteMathLogic::GetInstance().GetTotalWinFromGame();
    if (unWinFromGame != 0)
    {
        MainApp::GetInstance().ptrPanel->FastCollectCounting();
        MainApp::GetInstance().ptrPanel->ResetWin();
    }
    m_tableArea.ResetTableElements();
    RouletteMathLogic::GetInstance().ResetValuesToWinSector();
    LOG_INFO("Roulette - Stop Hold Timer, Reset Containers");
}