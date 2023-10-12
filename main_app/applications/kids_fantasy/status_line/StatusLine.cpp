#include "StatusLine.h"

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/panel/Panel.h>
#include <debug/Logger.h>

constexpr unsigned int g_unNormalScenarioTimer = 1;
constexpr unsigned int g_unNormalScenarioTimerPeriod = 4000;

constexpr unsigned int g_unFadeNormalScenario = 2;
constexpr unsigned int g_unFadeNormalScenarioPeriod = 1;

constexpr unsigned int g_unWinScenarioTimerFast = 3;
constexpr unsigned int g_unWinScenarioTimerFastPeriod = 1100;

constexpr unsigned int g_unWinScenarioTimerSlow = 4;
constexpr unsigned int g_unWinScenarioTimerSlowPeriod = 1100;

const std::string g_strInsertCredit = "INSERT CREDIT";
constexpr float g_fXInsetCredit = 830.0f;

const std::string g_strPressStart = "PRESS START TO RUN NEW GAME";
constexpr float g_fXPressStart = 660.0f;

const std::string g_strPlayAtMaxBet = "PLAY ON MAX BET";
constexpr float g_fXPlayAtMaxBet = 795.0f;

const std::string g_strWinTheMaxAmout = "WIN THE MAX AMOUNT";
constexpr float g_fXWinTheMaxAmount = 755.0f;

const std::string g_strGoodLuck = "GOOD LUCK!";
constexpr float g_fXGoodLuck = 843.0f;

const std::string g_strLine = "LINE ";

constexpr float g_fYLineFigureTextureOffset = 45.0f;

constexpr float g_fYStatusLine = 900.0f;

bool StatusLine::Init()
{
    m_fontStatusLine = Font::CreateFont("../src/fonts/Nasa.ttf", 40);

    if (!m_fontStatusLine->LoadFont())
    {
        LOG_ERROR("StatusLine - Unable to load font status line !");
        return false;
    }

    for (unsigned int i = GameDefs::eGameFigureOne; i < GameDefs::eTotalGameFiguresCount; ++i)
    {
        std::string strPath = "../src/resources/kids_fantasy/status_line/figure_small_" + std::to_string(i + 1) + ".png";
        m_arrSmallFigureTextures[i] = Texture::CreateTexture(strPath);

        if (!m_arrSmallFigureTextures[i]->Load())
        {
            LOG_ERROR("StatusLine - Unable to load font status line texture \"{0}\"", strPath);
            return false;
        }
    }

    m_eCurrentScenario = eInsertCredit;

    LOG_INFO("StatusLine - Initialized ...");
    return true;
}

bool StatusLine::Deinit()
{
    LOG_WARN("StatusLine - Deinitialized ...");
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

    case eWinFromLines:
    {
        if (m_bShowWinScenario)
        {
            /*Calculating positions*/
            auto textureFigure = m_arrSmallFigureTextures[m_currentWinElement.eGameFigure];
            std::string strTextLine = g_strLine + std::to_string(m_currentWinElement.eLine + 1) + "  ";
            std::string strFloatToString = " " + std::to_string(m_currentWinElement.fWin);
            std::string strTextWin = strFloatToString.substr(0, strFloatToString.find(".") + 3);
            unsigned char m_ucWidthChar = 15;
            float fWidthLineNumber = strTextLine.length() * m_ucWidthChar;
            float fWidthFiguresTexture = textureFigure->GetWidth() * m_currentWinElement.unFigureCount;
            float fWidthWin = strTextWin.length() * m_ucWidthChar;
            float fTotalWidthStatusLine = fWidthLineNumber + fWidthFiguresTexture + fWidthWin;
            float fXStatusLine = (rend->SCREEN_WIDTH - fTotalWidthStatusLine) / 2.0f;

            /*Draw Text Line*/
            rend->DrawText(strTextLine, m_fontStatusLine, fXStatusLine, g_fYStatusLine);

            /*Draw Small figures*/
            for (unsigned int i = 0; i < m_currentWinElement.unFigureCount; ++i)
            {
                float fXTexutre = (fXStatusLine + fWidthLineNumber) + (textureFigure->GetWidth() * i);
                float fYTexture = (g_fYStatusLine - g_fYLineFigureTextureOffset);

                rend->DrawPicture(textureFigure, fXTexutre, fYTexture);
            }

            /*Draw Win from line*/
            float fXWinFromFigure = (fXStatusLine + fWidthLineNumber + fWidthFiguresTexture);
            rend->DrawText(strTextWin, m_fontStatusLine, fXWinFromFigure, g_fYStatusLine);
        }
    }
    break;

    default:
        LOG_ERROR("StatusLine - Invalid StatusLine Scenario !");

        break;
    }

    rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void StatusLine::StartNormalScenario()
{
    m_fAlphaScenario = 1.0f;
    m_eCurrentScenario = eInsertCredit;
    NextNormalScenario();
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unNormalScenarioTimer, g_unNormalScenarioTimerPeriod);
    LOG_INFO("StatusLine - Normal Scenario Started");
}

void StatusLine::StopNormalScenario()
{
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unNormalScenarioTimer);
    LOG_INFO("StatusLine - Normal Scenario Stopped");
}

void StatusLine::StartWinScenario()
{
    m_unIndexWinElement = 0;
    m_currentWinElement = MathLogic::GetInstance().GetWinElements().at(m_unIndexWinElement);
    m_eCurrentScenario = eWinFromLines;
    m_fAlphaScenario = 1.0f;
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unWinScenarioTimerFast, g_unWinScenarioTimerFastPeriod);

    LOG_INFO("StatusLine - Win Scenario Started");
}

void StatusLine::StopWinScenario()
{
    m_unIndexWinElement = 0;
    m_fAlphaScenario = 1.0f;
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unWinScenarioTimerFast);
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unWinScenarioTimerSlow);
    LOG_INFO("StatusLine - Win Scenario Stopped");
}

void StatusLine::NextNormalScenario()
{
    if (!MainApp::GetInstance().ptrPanel->CanStartNewGame())
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

void StatusLine::NeedToShowGoodLuckScenario()
{
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unNormalScenarioTimer);
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unFadeNormalScenario);
    m_eCurrentScenario = eGoodLuck;
    m_fAlphaScenario = 1.0f;
    m_bShowWinScenario = true;
    LOG_INFO("StatusLine - Need To Show GOOD LUCK");
}

void StatusLine::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unNormalScenarioTimer)
    {
        /*When period reached, change scenario*/
        MainApp::GetInstance().ptrTimer->StartTimer(this, g_unFadeNormalScenario, g_unFadeNormalScenarioPeriod);
    }

    if (unID == g_unFadeNormalScenario)
    {
        const float fFadeSteps = 0.005f;
        m_fAlphaScenario -= fFadeSteps;

        if (m_fAlphaScenario <= 0.0f)
        {
            NextNormalScenario();
            MainApp::GetInstance().ptrTimer->StopTimer(this, g_unFadeNormalScenario);
            m_fAlphaScenario = 1.0f;
        }
    }

    if (unID == g_unWinScenarioTimerFast)
    {
        m_bShowWinScenario = !m_bShowWinScenario;
        if (m_bShowWinScenario)
        {
            return;
        }

        if (++m_unIndexWinElement >= MathLogic::GetInstance().GetWinElements().size())
        {
            m_unIndexWinElement = 0;
            MainApp::GetInstance().ptrTimer->StopTimer(this, g_unWinScenarioTimerFast);
            MainApp::GetInstance().ptrTimer->StartTimer(this, g_unWinScenarioTimerSlow, g_unWinScenarioTimerSlowPeriod);
            m_bShowWinScenario = false;
        }

        m_currentWinElement = MathLogic::GetInstance().GetWinElements().at(m_unIndexWinElement);
    }

    if (unID == g_unWinScenarioTimerSlow)
    {
        m_bShowWinScenario = !m_bShowWinScenario;
        if (m_bShowWinScenario)
        {
            return;
        }

        if (++m_unIndexWinElement >= MathLogic::GetInstance().GetWinElements().size())
        {
            m_unIndexWinElement = 0;
        }

        m_currentWinElement = MathLogic::GetInstance().GetWinElements().at(m_unIndexWinElement);
    }
}