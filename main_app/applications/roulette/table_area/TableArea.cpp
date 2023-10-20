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
constexpr float g_fXOffsetBethipsTable = 3.0f;
constexpr float g_fYOffsetBethipsTable = -121.0f;

constexpr float g_fYMaxBetChips = g_fYTableBets + g_fYOffsetBetChips - 80.0f;
constexpr float g_fYMinBetChips = g_fYTableBets + g_fYOffsetBetChips;
constexpr unsigned int g_unDurationSelectionChips = 200;

bool TableArea::Init()
{
    m_textureTableBets = Texture::CreateTexture("../src/resources/roulette/table_bets/table_bets.png");
    m_textureChipsTable = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_table.png");

    m_arrBetChips.at(GameDefs::eChip_1).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_1.png");
    m_arrBetChips.at(GameDefs::eChip_5).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_5.png");
    m_arrBetChips.at(GameDefs::eChip_10).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_10.png");
    m_arrBetChips.at(GameDefs::eChip_25).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_25.png");
    m_arrBetChips.at(GameDefs::eChip_100).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_100.png");
    m_arrBetChips.at(GameDefs::eChip_500).buttonChip.textureButton = Texture::CreateTexture("../src/resources/roulette/table_bets/chip_500.png");

    m_arrBetChips.at(GameDefs::eChip_1).buttonChip.fValue = 1.0f;
    m_arrBetChips.at(GameDefs::eChip_5).buttonChip.fValue = 5.0f;
    m_arrBetChips.at(GameDefs::eChip_10).buttonChip.fValue = 10.0f;
    m_arrBetChips.at(GameDefs::eChip_25).buttonChip.fValue = 25.0f;
    m_arrBetChips.at(GameDefs::eChip_100).buttonChip.fValue = 100.0f;
    m_arrBetChips.at(GameDefs::eChip_500).buttonChip.fValue = 500.0f;

    if (!m_textureTableBets->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture table bets !");
        return false;
    }

    if (!m_textureChipsTable->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture chips table !");
        return false;
    }

    m_buttonTableBets.textureButton = m_textureTableBets;
    m_buttonTableBets.fX = g_fXTableBets;
    m_buttonTableBets.fY = g_fYTableBets;

    for (unsigned int i = 0; i < m_arrBetChips.size(); ++i)
    {
        auto &chip = m_arrBetChips[i];

        if (!chip.buttonChip.textureButton->Load())
        {
            LOG_ERROR("TableArea - Unable to load texture chip !");
            return false;
        }

        chip.buttonChip.fX = g_fXTableBets + g_fXOffsetBetChips + (g_fXOffsetFromBetChips * i);
        chip.buttonChip.fY = g_fYTableBets + g_fYOffsetBetChips;
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
        /*If credit available, unlock chips*/
        if (fAvalableCredit < chip.buttonChip.fValue)
        {
            chip.buttonChip.colorButton.a = 0.3f;
            chip.buttonChip.bIsLocked = true;
            continue;
        }

        chip.buttonChip.bIsLocked = false;

        /*Press Chip*/
        if (chip.buttonChip.IsPressed(nXMouse, nYMouse))
        {
            chip.buttonChip.colorButton.a = 0.7f;
            chip.bIsSelectedForBet = !chip.bIsSelectedForBet;

            /*If selected, goes up else goes down*/
            if (chip.bIsSelectedForBet)
            {
                chip.m_interpolatorChipUp.Start(chip.buttonChip.fY, chip.buttonChip.fY, g_fYMaxBetChips, Ease::SineIn, g_unDurationSelectionChips);
                m_bIsAnyChipSelected = true;
            }
            else
            {
                chip.m_interpolatorChipDown.Start(chip.buttonChip.fY, chip.buttonChip.fY, g_fYMinBetChips, Ease::SineOut, g_unDurationSelectionChips);
                m_bIsAnyChipSelected = false;
            }

            return true;
        }
        /*Hover on Chip*/
        else if (chip.buttonChip.IsHovered(nXMouse, nYMouse))
        {
            chip.buttonChip.colorButton.a = 1.0f;
        }
        else
        {
            /*If up, increment alpha*/
            if (chip.bIsSelectedForBet)
            {
                chip.buttonChip.colorButton.a = 1.0f;
            }
            else
            {
                chip.buttonChip.colorButton.a = 0.7f;
            }
        }
    }

    return false;
}

void TableArea::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Table Bets*/
    rend->SetColor(m_buttonTableBets.colorButton.r, m_buttonTableBets.colorButton.g, m_buttonTableBets.colorButton.b, m_buttonTableBets.colorButton.a);
    rend->DrawPicture(m_buttonTableBets.textureButton, m_buttonTableBets.fX, m_buttonTableBets.fY);
    rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

    /*Chips Table*/
    rend->DrawPicture(m_textureChipsTable, g_fXTableBets + g_fXOffsetBethipsTable, g_fYTableBets + g_fYOffsetBethipsTable);

    /*Draw Bet Chip*/
    for (auto &chip : m_arrBetChips)
    {
        rend->SetColor(chip.buttonChip.colorButton.r, chip.buttonChip.colorButton.g, chip.buttonChip.colorButton.b, chip.buttonChip.colorButton.a);
        rend->DrawPicture(chip.buttonChip.textureButton, chip.buttonChip.fX, chip.buttonChip.fY);
        rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
}