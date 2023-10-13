#include "TableArea.h"

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr float g_fXTableBets = 920.0f;
constexpr float g_fYTableBets = 300.0f;

bool TableArea::Init()
{
    m_textureTableBets = Texture::CreateTexture("../src/resources/roulette/table_bets/table_bets.png");

    if (!m_textureTableBets->Load())
    {
        LOG_ERROR("TableArea - Unable to load texture table bets !");
        return false;
    }

    LOG_INFO("Table Area - Initialized ...");
    return true;
}

bool TableArea::Deinit()
{
    LOG_WARN("Table Area - Deinitialized ...");
    return true;
}

void TableArea::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;
    
    rend->DrawPicture(m_textureTableBets, g_fXTableBets, g_fYTableBets);
}