#include "ReelsArea.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/applications/kids_fantasy/math_logic/MathLogic.h>
#include <debug/Logger.h>

constexpr float g_fXReelsArea = 25.0;
constexpr float g_fYReelsArea = 0.0f;

constexpr float g_fXOrgPosReel1 = 316.0f;
constexpr float g_fXOrgPosReel2 = 566.0f;
constexpr float g_fXOrgPosReel3 = 815.0f;
constexpr float g_fXOrgPosReel4 = 1063.0f;
constexpr float g_fXOrgPosReel5 = 1312.0f;

constexpr float g_fYOrgPosReels = 165.0f;

bool ReelsArea::Init()
{

    /*Load textures*/
    m_textureReelsArea = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reels_area_clean.png");

    if (!m_textureReelsArea->Load())
    {
        LOG_ERROR("Reels Area - Unable to load texture reels area !");
        return false;
    }

    /*Figures Texutre*/
    m_arrFiguresTexture.at(GameDefs::eGameFigureOne) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_1.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureTwo) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_2.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureThree) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_3.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureFour) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_4.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureFive) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_5.png");
    m_arrFiguresTexture.at(GameDefs::eGameFigureSix) = Texture::CreateTexture("../src/resources/kids_fantasy/reels_area/reel_figures/figure_6.png");

    for(auto& texture : m_arrFiguresTexture)
    {
        if(!texture->Load())
        {
            LOG_ERROR("Reels Area - Unable to load texture figure \"{0}\"", texture->GetPath());
            return false;
        }
    }

    /*Initialize Reels*/
    if (!m_arrReels.at(GameDefs::eFirstReel).Init(GameDefs::eFirstReel, 
                                                    g_fXReelsArea + g_fXOrgPosReel1, 
                                                    g_fYReelsArea + g_fYOrgPosReels,
                                                    m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 1!");
        return false;
    }
    if (!m_arrReels.at(GameDefs::eSecondReel).Init(GameDefs::eSecondReel, 
                                                    g_fXReelsArea + g_fXOrgPosReel2, 
                                                    g_fYReelsArea + g_fYOrgPosReels,
                                                    m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 2!");
        return false;
    }
    if (!m_arrReels.at(GameDefs::eThirdReel).Init(GameDefs::eThirdReel, 
                                                    g_fXReelsArea + g_fXOrgPosReel3, 
                                                    g_fYReelsArea + g_fYOrgPosReels,
                                                    m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 3 !");
        return false;
    }
    if (!m_arrReels.at(GameDefs::eFourthReel).Init(GameDefs::eFourthReel, 
                                                    g_fXReelsArea + g_fXOrgPosReel4, 
                                                    g_fYReelsArea + g_fYOrgPosReels,
                                                    m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 4 !");
        return false;
    }
    if (!m_arrReels.at(GameDefs::eFifthReel).Init(GameDefs::eFifthReel, 
                                                    g_fXReelsArea + g_fXOrgPosReel5, 
                                                    g_fYReelsArea + g_fYOrgPosReels,
                                                    m_arrFiguresTexture))
    {
        LOG_ERROR("Reels Area - Unable to load reel 5!");
        return false;
    }

    LOG_INFO("Reels Area - Initialized ...");
    return true;
}

bool ReelsArea::Deinit()
{
    LOG_INFO("Reels Area - Deinitialized ...");
    return true;
}

bool ReelsArea::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;

    /*Enter Button*/
    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter), false))
    {
        /*Start Reeling when ENTER pressed*/
        bool bCanStartReeling = true;
        for (auto &reel : m_arrReels)
        {
            if (reel.GetReelState() != EReelState::eStopped)
            {
                bCanStartReeling = false;
                break;
            }
        }

        if (bCanStartReeling)
        {
            /*Generate New Results*/
            MathLogic::GetInstance().GenerateResults();
            
            for (auto &reel : m_arrReels)
            {
                reel.StartReeling();
            }
        }

        LOG_INFO("Reels Area - ENTER Pressed");
        return true;
    }

    return false;
}

void ReelsArea::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Reels Area*/
    rend->DrawPicture(m_textureReelsArea, 25.0f, 0.0f);

    /*Draw Reels*/
    for (auto &reel : m_arrReels)
    {
        reel.Draw();
    }
}