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

    /*Register Client Kids Fantasy*/
    RegisterClient(EApps::eKidsFantasy, &m_KidsFantasy);

    /*Initalize all the applications*/
    for(const auto& app : m_mapAppClients)
    {
        if(!app.second->Init())
        {
            LOG_ERROR("AppSelect - Cannot initialize client : \"{0}\"", app.second->GetAppName());
            break;
        }
    }

    m_eState = EAppSelectStates::eReadyForSelection;

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

    switch (m_eState)
    {
    case EAppSelectStates::eReadyForSelection:
    {
        m_bIsKidsFantasyHovered = m_buttonKidsFantasy.IsHovered(nXMouse, nYMouse);
        if(m_bIsKidsFantasyHovered)
        {
            /*Select Kids Fantasy*/
            if(m_buttonKidsFantasy.IsPressed(nXMouse, nYMouse))
            {
                m_eCurrentApp = EApps::eKidsFantasy;
                m_eState = EAppSelectStates::eBusyInGame;
                m_mapAppClients[m_eCurrentApp]->OnEnter();

                return true;
            }

            return true;
        }

        m_bIsRouletteHovered = m_buttonRoulette.IsHovered(nXMouse, nYMouse);
        if(m_bIsRouletteHovered)
        {
            return true;
        }
    }
        break;

    case EAppSelectStates::eBusyInGame:
    {
        m_mapAppClients[m_eCurrentApp]->HandleEvent();
    }
        break;
    
    default:
        break;
    }

    return false;
}

const EAppSelectStates& AppSelect::GetState()
{
    return m_eState;
}

void AppSelect::RegisterClient(EApps eApp, IApp* client)
{
    m_mapAppClients.emplace(std::make_pair(eApp, client));

    LOG_INFO("AppSelect - Registered client : \"{0}\"", client->GetAppName());
    LOG_INFO("AppSelect - Current size of AppClientsContainer: \"{0}\"", m_mapAppClients.size());
}

void AppSelect::UnregisterClient(EApps eApp, IApp* client)
{
    const auto& it = m_mapAppClients.find(eApp);
    if(it != m_mapAppClients.end())
    {
        LOG_INFO("AppSelect - Unregistered client : \"{0}\"", it->second->GetAppName());
        m_mapAppClients.erase(eApp);
    }

    LOG_INFO("AppSelect - Current size of AppClientsContainer: \"{0}\"", m_mapAppClients.size());
}

void AppSelect::OnDraw()
{
    const auto& rend = MainApp::GetInstance().ptrRend;

    switch (m_eState)
    {
    case EAppSelectStates::eReadyForSelection:
    {
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
        break;

    case EAppSelectStates::eBusyInGame:
    {
        m_mapAppClients[m_eCurrentApp]->OnDraw();
    }
        break;
    
    default:
        break;
    }


}
