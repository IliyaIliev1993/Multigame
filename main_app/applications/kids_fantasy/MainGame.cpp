#include "MainGame.h"

#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <main_app/applications/kids_fantasy/math_logic/MathLogic.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerGameCycle = 1;

KidsFantasy::KidsFantasy()
{
}

bool KidsFantasy::Init()
{

    /*Load textures*/
    m_textureBackground = Texture::CreateTexture("../src/resources/kids_fantasy/kids_fantasy_background.png");

    if (!m_textureBackground->Load())
    {
        LOG_ERROR("KidsFantasy - Unable to load texture background !");
        return false;
    }

    /*MathLogic Init*/
    if (!MathLogic::GetInstance().Init())
    {
        LOG_ERROR("Kids Fantasy - Unable to Init Math Logic !");
        return false;
    }

    /*Reels Area Init*/
    if (!m_reelsArea.Init())
    {
        LOG_ERROR("Kids Fantasy - Unable to Init Reels Area !");
        return false;
    }

    if (!m_statusLine.Init())
    {
        LOG_ERROR("Kids Fantasy - Unable to Init StatusLine !");
        return false;
    }

    /*Set after reeling stopped callback*/
    std::function<void()> afterReelingStopped = [this]()
    {
        AfterReelingStopped();
    };
    m_reelsArea.SetAfterReelingStoppedCallback(afterReelingStopped);

    LOG_INFO("Kids Fantasy - Initialized ...");
    return true;
}

bool KidsFantasy::Deinit()
{
    /*Reels Area Deinit*/
    m_reelsArea.Deinit();

    /*StatusLine Deinit*/
    m_statusLine.Deinit();

    /*Math Logic Deinit*/
    MathLogic::GetInstance().Deinit();

    LOG_INFO("Kids Fantasy - Deinitialized ...");
    return true;
}

bool KidsFantasy::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;

    /*Panel Handle Event*/
    if (m_eState == EKidsFantasyStates::eReadyForGame)
    {
        MainApp::GetInstance().ptrPanel->HandleEvent();
    }

    /*Enter Button*/
    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter), false))
    {
        LOG_INFO("Kids Fantasy - ENTER Button Pressed");

        /*Take money counting and request ready for game*/
        if(m_eState == EKidsFantasyStates::eWinFromGame)
        {
            m_statusLine.StopWinScenario();
            RequestState(EKidsFantasyStates::eReadyForGame);
        }

        /*Start new Game*/
        if (m_eState == EKidsFantasyStates::eReadyForGame &&
            m_reelsArea.StartNewGame())
        {
            RequestState(EKidsFantasyStates::eReeling);
            m_statusLine.NeedToShowGoodLuckScenario();
        }

        return true;
    }

    /*Reels Area Handle Event*/
    m_reelsArea.HandleEvent();

    return false;
}

const std::string &KidsFantasy::GetAppName()
{
    return m_strAppName;
}

void KidsFantasy::RequestState(EKidsFantasyStates eStateToRequest)
{
    std::string strStateToRequest = "N/A";
    std::string strCurrentState = "N/A";

    /*Current State*/
    switch (m_eState)
    {
    case EKidsFantasyStates::eInactive:
    {
        strCurrentState = "eInactive";
    }
    break;

    case EKidsFantasyStates::eReadyForGame:
    {
        strCurrentState = "eReadyForGame";
    }
    break;

    case EKidsFantasyStates::eReeling:
    {
        strCurrentState = "eReeling";
    }
    break;

    case EKidsFantasyStates::eAfterReelingStopped:
    {
        strCurrentState = "eAfterReelingStopped";
    }
    break;

    case EKidsFantasyStates::eWinFromGame:
    {
        strCurrentState = "eWinFromGame";
    }
    break;

    default:
        break;
    }

    /*State to Request*/
    switch (eStateToRequest)
    {
    case EKidsFantasyStates::eInactive:
    {
        strStateToRequest = "eInactive";

        if (m_eState == EKidsFantasyStates::eReadyForGame)
        {
            LOG_INFO("Kids Fantasy - Possible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
            m_eState = eStateToRequest;
        }
        else
        {
            LOG_ERROR("Kids Fantasy - Impossible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
        }
    }
    break;

    case EKidsFantasyStates::eReadyForGame:
    {
        strStateToRequest = "eReadyForGame";

        if (m_eState == EKidsFantasyStates::eInactive ||
            m_eState == EKidsFantasyStates::eAfterReelingStopped ||
            m_eState == EKidsFantasyStates::eWinFromGame)
        {
            LOG_INFO("Kids Fantasy - Possible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
            m_eState = eStateToRequest;
        }
        else
        {
            LOG_ERROR("Kids Fantasy - Impossible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
        }
    }
    break;

    case EKidsFantasyStates::eReeling:
    {
        strStateToRequest = "eReeling";

        if (m_eState == EKidsFantasyStates::eReadyForGame)
        {
            LOG_INFO("Kids Fantasy - Possible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
            m_eState = eStateToRequest;
        }
        else
        {
            LOG_ERROR("Kids Fantasy - Impossible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
        }
    }
    break;

    case EKidsFantasyStates::eAfterReelingStopped:
    {
        strStateToRequest = "eAfterReelingStopped";

        if (m_eState == EKidsFantasyStates::eReeling)
        {
            LOG_INFO("Kids Fantasy - Possible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
            m_eState = eStateToRequest;
        }
        else
        {
            LOG_ERROR("Kids Fantasy - Impossible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
        }
    }
    break;

    case EKidsFantasyStates::eWinFromGame:
    {
        strStateToRequest = "eWinFromGame";

        if (m_eState == EKidsFantasyStates::eAfterReelingStopped)
        {
            LOG_INFO("Kids Fantasy - Possible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
            m_eState = eStateToRequest;
        }
        else
        {
            LOG_ERROR("Kids Fantasy - Impossible request state: \"{0}\" -> \"{1}\"", strCurrentState, strStateToRequest);
        }
    }
    break;

    default:
        break;
    }
}

void KidsFantasy::OnEnter()
{
    LOG_INFO("Kids Fantasy - Transition to Application succeed");

    RequestState(EKidsFantasyStates::eReadyForGame);
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerGameCycle, 1);
    m_statusLine.StartNormalScenario();
}

void KidsFantasy::OnExit()
{
    m_statusLine.StopNormalScenario();
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerGameCycle);
    RequestState(EKidsFantasyStates::eInactive);

    LOG_INFO("Kids Fantasy - Exit from Application");
}

void KidsFantasy::OnDraw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Background*/
    rend->DrawPicture(m_textureBackground, 0.0f, 0.0f);

    /*Draw ReelsArea*/
    m_reelsArea.Draw();

    /*Draw StatusLine*/
    m_statusLine.Draw();

    /*Draw Panel*/
    MainApp::GetInstance().ptrPanel->OnDraw();
}

void KidsFantasy::AfterReelingStopped()
{
    RequestState(EKidsFantasyStates::eAfterReelingStopped);

    /*After the reeling stops, check if there is a win*/
    if(MathLogic::GetInstance().ThereIsAWin())
    {
        RequestState(EKidsFantasyStates::eWinFromGame);
        m_statusLine.StartWinScenario();
    }
    else
    {
        RequestState(EKidsFantasyStates::eReadyForGame);
        m_statusLine.StartNormalScenario();
    }
}

void KidsFantasy::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerGameCycle)
    {
    }
}