#include "Panel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/app_select/AppSelect.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr float g_fXHomeButton = 0.0f;
constexpr float g_fYHomeButton = 920.0f;

bool Panel::Init()
{
    m_textureHomeButton = Texture::CreateTexture("../src/resources/panel/home_button.png");
    m_textureHomeButtonPressed = Texture::CreateTexture("../src/resources/panel/home_button_pressed.png");

    if(!m_textureHomeButton->Load())
    {
        LOG_ERROR("Panel - Unable to load texture home button !");
        return false;
    }

    if(!m_textureHomeButtonPressed->Load())
    {
        LOG_ERROR("Panel - Unable to load texture home button pressed!");
        return false;
    }

    m_homeButton.textureButton = m_textureHomeButton;
    m_homeButton.fX = g_fXHomeButton;
    m_homeButton.fY = g_fYHomeButton;

    LOG_INFO("Panel - Initialized ...");
    return true;
}

bool Panel::Deinit()
{
    return true;
}

bool Panel::HandleEvent()
{
    const auto& nXMouse = ImGui::GetMousePos().x;
    const auto& nYMouse = ImGui::GetMousePos().y;

    if(m_homeButton.IsPressAndHold(nXMouse, nYMouse))
    {
        m_homeButton.textureButton = m_textureHomeButtonPressed;
        return true;
    }
    else
    {
        m_homeButton.textureButton = m_textureHomeButton;

        /*When button relaesed, request transition to app select*/
        if(m_homeButton.IsReleased(nXMouse, nYMouse))
        {
            MainApp::GetInstance().ptrAppSelect->RequestTransition(EApps::eAppSelect);
            return true;
        }
    }

    return false;
}

void Panel::OnDraw()
{
    const auto& rend = MainApp::GetInstance().ptrRend;

    /*Home Button*/
    rend->DrawPicture(m_homeButton.textureButton, m_homeButton.fX, m_homeButton.fY);
}
