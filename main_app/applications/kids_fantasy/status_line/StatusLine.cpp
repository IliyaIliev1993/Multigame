#include "StatusLine.h"

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <debug/Logger.h>

constexpr unsigned int g_unStatusLineScenarioTimer = 1;
constexpr unsigned int g_unStatusLineScenarioTimerPeriod = 4000;

constexpr unsigned int g_unFadeScenario = 2;
constexpr unsigned int g_unFadeScenarioPeriod = 1;

const std::string g_strInsertCredit = "INSERT CREDIT";
constexpr float g_fXInsetCredit = 830.0f;

const std::string g_strPressStart = "PRESS START TO RUN NEW GAME";
constexpr float g_fXPressStart = 660.0f;

const std::string g_strPlayAtMaxBet = "PLAY AT MAX BET";
constexpr float g_fXPlayAtMaxBet = 795.0f;

const std::string g_strWinTheMaxAmout = "WIN THE MAX AMOUNT";
constexpr float g_fXWinTheMaxAmount = 755.0f;

const std::string g_strGoodLuck = "GOOD LUCK!";
constexpr float g_fXGoodLuck = 843.0f;

constexpr float g_fYStatusLine = 900.0f;

bool StatusLine::Init()
{
    m_fontStatusLine = Font::CreateFont("../src/fonts/Nasa.ttf", 40);

    if (!m_fontStatusLine->LoadFont())
    {
        LOG_ERROR("StatusLine - Unable to load font status line !");
        return false;
    }

    m_eCurrentScenario = eInsertCredit;

    LOG_INFO("StatusLine - Initialized ...");
    return true;
}

bool StatusLine::Deinit()
{
    LOG_INFO("StatusLine - Deinitialized ...");
    return true;
}

void StatusLine::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    rend->SetColor(1.0f, 1.0f, 1.0f, m_fAlphaScenario);

    switch (m_eCurrentScenario)
    {
    case eInsertCredit:
    {
        rend->DrawText(g_strInsertCredit, m_fontStatusLine, g_fXInsetCredit, g_fYStatusLine);
    }
    break;

    case ePressStartToRunNewGame:
    {
        rend->DrawText(g_strPressStart, m_fontStatusLine, g_fXPressStart, g_fYStatusLine);
    }
    break;

    case ePlayAtMaxBet:
    {
        rend->DrawText(g_strPlayAtMaxBet, m_fontStatusLine, g_fXPlayAtMaxBet, g_fYStatusLine);
    }
    break;

    case eWinTheMaxAmout:
    {
        rend->DrawText(g_strWinTheMaxAmout, m_fontStatusLine, g_fXWinTheMaxAmount, g_fYStatusLine);
    }
    break;

    case eGoodLuck:
    {
        rend->DrawText(g_strGoodLuck, m_fontStatusLine, g_fXGoodLuck, g_fYStatusLine);
    }
    break;

    default:
    LOG_ERROR("StatusLine - Invalid StatusLine Scenario !");

        break;
    }

    rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void StatusLine::StartScenario()
{
    m_fAlphaScenario = 1.0f;
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unStatusLineScenarioTimer, g_unStatusLineScenarioTimerPeriod);
    LOG_INFO("StatusLine - Scenario Started");
}

void StatusLine::StopScenario()
{
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unStatusLineScenarioTimer);
    LOG_INFO("StatusLine - Scenario Stopped");
}

void StatusLine::NextScenario()
{
    if(!MainApp::GetInstance().ptrPanel->CanStartNewGame())
    {
        m_eCurrentScenario = eInsertCredit;
        return;
    }

    switch (m_eCurrentScenario)
    {
    case eInsertCredit:
    {
        m_eCurrentScenario = ePressStartToRunNewGame;
    }
    break;

    case ePressStartToRunNewGame:
    {
        m_eCurrentScenario = ePlayAtMaxBet;
    }
    break;

    case ePlayAtMaxBet:
    {
        m_eCurrentScenario = eWinTheMaxAmout;
    }
    break;

    case eWinTheMaxAmout:
    {
        m_eCurrentScenario = ePressStartToRunNewGame;
    }
    break;

    default:
    LOG_ERROR("StatusLine - Invalid StatusLine Scenario !");

        break;
    }

}

void StatusLine::NeedToShowGoodLuck()
{
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unStatusLineScenarioTimer);
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unFadeScenario);
    m_eCurrentScenario = eGoodLuck;
    m_fAlphaScenario = 1.0f;
}

void StatusLine::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unStatusLineScenarioTimer)
    {
        /*When period reached, change scenario*/
        MainApp::GetInstance().ptrTimer->StartTimer(this, g_unFadeScenario, g_unFadeScenarioPeriod);
    }

    if(unID == g_unFadeScenario)
    {
        const float fFadeSteps = 0.005f;
        m_fAlphaScenario -= fFadeSteps;

        if(m_fAlphaScenario <= 0.0f)
        {
            NextScenario();
            MainApp::GetInstance().ptrTimer->StopTimer(this, g_unFadeScenario);
            m_fAlphaScenario = 1.0f;
        }
    }
}