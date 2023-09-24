#include "Reel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerReeling = 1;
constexpr unsigned int g_unPeriodReeling = 1;
constexpr float g_fReelingStep = 1.0f;
const std::string g_strFigurePath = "../src/resources/kids_fantasy/reels_area/reel_figures/";

bool Reel::Init(GameDefs::EReels eIDReel, float fXOrgPos, float fYOrgPos)
{
    m_eIDReel = eIDReel;
    m_fXOrgPos = fXOrgPos;
    m_fYOrgPos = fYOrgPos;

    m_fYMinTresholdReelingFigure = m_fYOrgPos - GameDefs::g_fHeightFigurePicture;
    m_fYMaxTresholdReelingFigure = m_fYOrgPos + (GameDefs::g_fHeightFigurePicture * GameDefs::g_unVisibleFiguresPerReel);

    for (unsigned int i = GameDefs::eFirstPositionNONVisible; i < GameDefs::eTotalFigurePositionsPerReel; ++i)
    {
        std::string strFigureID = g_strFigurePath + "figure_" + std::to_string(i + 1) + ".png";
        Figure figureObject;
        figureObject.textureFigure = Texture::CreateTexture(strFigureID);
        if (!figureObject.textureFigure->Load())
        {
            LOG_ERROR("Reel - Failed to load texture figure - \"{0}\"", strFigureID);
            return false;
        }

        figureObject.fXPos = m_fXOrgPos;
        figureObject.fYPos = m_fYOrgPos + (figureObject.textureFigure->GetHeight() * (i - 1));
        if (i == GameDefs::eFirstPositionNONVisible)
        {
            figureObject.fYPos = m_fYMinTresholdReelingFigure;
        }

        figureObject.eGameFigure = GameDefs::EGameFigure::eGameFigureOne;
        figureObject.eFigurePosition = (GameDefs::EFigurePositionPerReel)i;

        m_arrReelFigures.at(i) = figureObject;
    }

    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerReeling, g_unPeriodReeling);

    LOG_INFO("Reel - Initialized Reel with ID - \"{0}\"", (int)m_eIDReel);
    return true;
}

void Reel::ProcessReeling()
{
    int nIndexFigure = 0;
    for (auto &figure : m_arrReelFigures)
    {
        if (figure.fYPos > m_fYMaxTresholdReelingFigure)
        {
            int nIndexToBeInsertedAbove = nIndexFigure + 1;

            /*Behavior when we are at the last figure and we want to be inserted above the first*/
            if (nIndexToBeInsertedAbove > GameDefs::eFifthPositionNONVisible)
            {
                nIndexToBeInsertedAbove = GameDefs::eFirstPositionNONVisible;
            }

            figure.fYPos = m_arrReelFigures.at(nIndexToBeInsertedAbove).fYPos - GameDefs::g_fHeightFigurePicture;
        }

        //figure.fYPos += (g_fReelingStep + static_cast<float>(MainApp::GetInstance().GetDeltaTime()));

        figure.fYPos += g_fReelingStep;
        
        if (++nIndexFigure >= m_arrReelFigures.size())
        {
            nIndexFigure = 0;
        }
    }
}

void Reel::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    rend->UseShaderCrop(glm::vec4(m_fXOrgPos, m_fYOrgPos,
                                  GameDefs::g_fWidthFigurePicture,
                                  GameDefs::g_fHeightFigurePicture * GameDefs::g_unVisibleFiguresPerReel));

    for (const auto &figure : m_arrReelFigures)
    {
        rend->DrawPicture(figure.textureFigure, figure.fXPos, figure.fYPos);
    }

    rend->UseShaderPicture();
}

void Reel::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerReeling && unTimes >= 120)
    {
        ProcessReeling();
    }
}