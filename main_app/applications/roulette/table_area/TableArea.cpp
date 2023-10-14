#include "TableArea.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/panel/Panel.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr float g_fXTableBets = 920.0f;
constexpr float g_fYTableBets = 300.0f;

constexpr float g_fXOffsetFromBetChips = 170.0f;
constexpr float g_fXOffsetBetChips = 30.0f;
constexpr float g_fYOffsetBetChips = -100.0f;

bool TableArea::Init()
{
    m_textureTableBets = Texture::CreateTexture("../src/resources/roulette/table_bets/table_bets.png");
    m_arrBetChips.at(GameDefs::eChip_1).textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_1.png");
    m_arrBetChips.at(GameDefs::eChip_5).textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_5.png");
    m_arrBetChips.at(GameDefs::eChip_10).textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_10.png");
    m_arrBetChips.at(GameDefs::eChip_25).textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_25.png");
    m_arrBetChips.at(GameDefs::eChip_100).textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_100.png");
    m_arrBetChips.at(GameDefs::eChip_500).textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_500.png");

    m_arrBetChips.at(GameDefs::eChip_1).fValue = 1.0f;
    m_arrBetChips.at(GameDefs::eChip_5).fValue = 5.0f;
    m_arrBetChips.at(GameDefs::eChip_10).fValue = 10.0f;
    m_arrBetChips.at(GameDefs::eChip_25).fValue = 25.0f;
    m_arrBetChips.at(GameDefs::eChip_100).fValue = 100.0f;
    m_arrBetChips.at(GameDefs::eChip_500).fValue = 500.0f;

    if (!m_textureTableBets->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture table bets !");
        return false;
    }

    for (unsigned int i = 0; i < m_arrBetChips.size(); ++i)
    {
        auto &chip = m_arrBetChips[i];

        if (!chip.textureButton->Load())
        {
            LOG_ERROR("TableArea - Unable to load texture chip !");
            return false;
        }

        chip.fX = g_fXTableBets + g_fXOffsetBetChips + (g_fXOffsetFromBetChips * i);
        chip.fY = g_fYTableBets + g_fYOffsetBetChips;
    }

    LOG_INFO("Table Area - Initialized ...");
    return true;
}

bool TableArea::Deinit()
{
    LOG_WARN("Table Area - Deinitialized ...");
    return true;
}

bool TableArea::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;

    const auto &fAvalableCredit = MainApp::GetInstance().ptrPanel->GetAvailableCredit();

    for (auto &chip : m_arrBetChips)
    {
        if(fAvalableCredit < chip.fValue)
        {
            chip.colorButton.a = 0.5f;
            chip.bIsLocked = true;
            continue;
        }

        chip.bIsLocked = false;

        /*Hover over Chip*/
        if (chip.IsHovered(nXMouse, nYMouse))
        {
            chip.colorButton.a = 0.5f;
            return true;
        }
        else
        {
            chip.colorButton.a = 1.0f;
        }
    }

    return false;
}

void TableArea::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Table Bets*/
    rend->DrawPicture(m_textureTableBets, g_fXTableBets, g_fYTableBets);

    /*Draw Bet Chip*/
    for (auto &chip : m_arrBetChips)
    {
        rend->SetColor(chip.colorButton.r, chip.colorButton.g, chip.colorButton.b, chip.colorButton.a);
        rend->DrawPicture(chip.textureButton, chip.fX, chip.fY);
        rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
}