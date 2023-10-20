#include "MainGame.h"

#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <main_app/applications/roulette/math_logic/RouletteMathLogic.h>
#include <debug/Logger.h>

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

    if (ImGui::IsMouseClicked(0))
    {
        std::cout << "MOUSE:" << std::endl;
        std::cout << nXMouse << " " << nYMouse << std::endl;
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
    /*Generate new results*/
    RouletteMathLogic::GetInstance().GenerateResults();
    m_wheelArea.StartNewSpin();
}

void Roulette::OnEnter()
{
    m_wheelArea.StartSlowRotation();

    LOG_INFO("Roulette - Transition to Application succeed");
}

void Roulette::OnExit()
{
    m_wheelArea.StopSlowRotation();

    LOG_INFO("Roulette - Exit from Application");
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
}