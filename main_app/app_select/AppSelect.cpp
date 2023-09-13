#include "AppSelect.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr float g_fXKidsFantasyButton = 230.0f;
constexpr float g_fYKidsFantasyButton = 386.0f;

constexpr float g_fXRouletteButton = 1190.0f;
constexpr float g_fYRouletteButton = 386.0f;

bool AppSelect::Init()
{
    /*Load textures*/
    m_textureBackground = Texture::CreateTexture("../src/resources/app_select_background.jpg");

    m_buttonKidsFantasy.textureButton = Texture::CreateTexture("../src/resources/kids_fantasy/kids_fantasy_button_bgr_round.png");
    m_buttonKidsFantasy.fX = g_fXKidsFantasyButton;
    m_buttonKidsFantasy.fY = g_fYKidsFantasyButton;
    
    m_buttonRoulette.textureButton = Texture::CreateTexture("../src/resources/roulette/roulette_button.png");
    m_buttonRoulette.fX = g_fXRouletteButton;
    m_buttonRoulette.fY = g_fYRouletteButton;

    if(!m_textureBackground->Load())
    {
        LOG_ERROR("AppSelect - Unable to load texture background !");
        return false;
    }

    if(!m_buttonKidsFantasy.textureButton->Load())
    {
        LOG_ERROR("AppSelect - Unable to load texture kids fantasy button !");
        return false;
    }

    if(!m_buttonRoulette.textureButton->Load())
    {
        LOG_ERROR("AppSelect - Unable to load texture roulette button !");
        return false;
    }

    LOG_INFO("AppSelect - Initialized ...");
    return true;
}

bool AppSelect::Deinit()
{
    LOG_INFO("AppSelect - Deinitialzied ...");
    return true;
}

bool AppSelect::HandleEvent()
{
    /*Hover on Game Buttons*/
    const auto& nXMouse = ImGui::GetMousePos().x;
    const auto& nYMouse = ImGui::GetMousePos().y;

    m_bIsKidsFantasyHovered = m_buttonKidsFantasy.IsHovered(nXMouse, nYMouse);
    if(m_bIsKidsFantasyHovered)
    {
        return true;
    }

    m_bIsRouletteHovered = m_buttonRoulette.IsHovered(nXMouse, nYMouse);
    if(m_bIsRouletteHovered)
    {
        return true;
    }

    return false;
}

void AppSelect::RegisterClient(IApp *client)
{
    m_vecAppClients.emplace_back(client);

    LOG_INFO("AppSelect - Registered client : \"{0}\"", client->GetAppName());
    LOG_INFO("AppSelect - Current size of AppClientsContainer: \"{0}\"", m_vecAppClients.size());
}

void AppSelect::UnregisterClient(IApp *client)
{
    for(auto it = m_vecAppClients.begin(); it != m_vecAppClients.end(); ++it)
    {
        if(*it == client)
        {
            LOG_INFO("AppSelect - Unregistered client : \"{0}\"", client->GetAppName());
            m_vecAppClients.erase(it);
            break;
        }
    }

    LOG_INFO("AppSelect - Current size of AppClientsContainer: \"{0}\"", m_vecAppClients.size());
}

void AppSelect::OnDraw()
{
    const auto& rend = MainApp::GetInstance().ptrRend;
    
    /*Draw Background*/
    rend->DrawPicture(m_textureBackground, 0.0f, 0.0f);

    /*Draw Button Kids Fantasy*/
    if(m_bIsKidsFantasyHovered)
    {
        rend->SetColor(1.0f, 1.0f, 1.0f, 0.5f);
    }

    rend->DrawPicture(m_buttonKidsFantasy.textureButton, m_buttonKidsFantasy.fX, m_buttonKidsFantasy.fY);

    if(m_bIsKidsFantasyHovered)
    {
        rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    /*Draw Button Roulette*/
    if(m_bIsRouletteHovered)
    {
        rend->SetColor(1.0f, 1.0f, 1.0f, 0.5f);
    }

    rend->DrawPicture(m_buttonRoulette.textureButton, m_buttonRoulette.fX, m_buttonRoulette.fY);

    if(m_bIsRouletteHovered)
    {
        rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

}
