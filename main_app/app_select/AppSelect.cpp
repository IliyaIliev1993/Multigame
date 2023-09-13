#include "AppSelect.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

bool AppSelect::Init()
{
    /*Load textures*/
    m_textureBackground = Texture::CreateTexture("../src/resources/app_select_background.jpg");
    m_textureKidsFantasyButton = Texture::CreateTexture("../src/resources/kids_fantasy/kids_fantasy_button_bgr_round.png");
    m_textureRouletteButton = Texture::CreateTexture("../src/resources/roulette/roulette_button.png");

    if(!m_textureBackground->Load())
    {
        LOG_ERROR("AppSelect - Unable to load texture background !");
        return false;
    }

    if(!m_textureKidsFantasyButton->Load())
    {
        LOG_ERROR("AppSelect - Unable to load texture kids fantasy button !");
        return false;
    }

    if(!m_textureRouletteButton->Load())
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
    rend->DrawPicture(m_textureKidsFantasyButton, 230.0f, 386.0f);

    /*Draw Button Roulette*/
    rend->DrawPicture(m_textureRouletteButton, 1190.0f, 386.0f);

}
