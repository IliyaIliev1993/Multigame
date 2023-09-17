#include "Panel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/app_select/AppSelect.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr float g_fXHomeButton = 0.0f;
constexpr float g_fYHomeButton = 920.0f;

constexpr float g_fXVolumeButton = 1720.0f;
constexpr float g_fYVolumeButton = 880.0f;
constexpr float g_fXVolumeKnobButton = 1765.0f;
constexpr float g_fYVolumeKnobButton = 925.0f;

constexpr float g_fMaxTresholdVolumeDegrees = 335.0f;

bool Panel::Init()
{
    m_textureHomeButton = Texture::CreateTexture("../src/resources/panel/home_button.png");
    m_textureHomeButtonPressed = Texture::CreateTexture("../src/resources/panel/home_button_pressed.png");
    m_textureVolumeButton = Texture::CreateTexture("../src/resources/panel/volume_button.png");
    m_textureVolumeKnob = Texture::CreateTexture("../src/resources/panel/knob_volume.png");

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

    if(!m_textureVolumeButton->Load())
    {
        LOG_ERROR("Panel - Unable to load texture volume button!");
        return false;
    }

    if(!m_textureVolumeKnob->Load())
    {
        LOG_ERROR("Panel - Unable to load texture volume knob!");
        return false;
    }

    m_homeButton.textureButton = m_textureHomeButton;
    m_homeButton.fX = g_fXHomeButton;
    m_homeButton.fY = g_fYHomeButton;

    m_volumeKnobButton.textureButton = m_textureVolumeKnob;
    m_volumeKnobButton.fX = g_fXVolumeKnobButton;
    m_volumeKnobButton.fY = g_fYVolumeKnobButton;

    LOG_INFO("Panel - Initialized ...");
    return true;
}

bool Panel::Deinit()
{
    LOG_INFO("Panel - Deinitialized ...");
    return true;
}

bool Panel::HandleEvent()
{
    const auto& nXMouse = ImGui::GetMousePos().x;
    const auto& nYMouse = ImGui::GetMousePos().y;

    /*Volume Button*/
    if(m_volumeKnobButton.IsPressed(nXMouse, nYMouse))
    {
        m_bVolumeKnobModify = true;
    }
    if(m_volumeKnobButton.IsReleased(nXMouse, nYMouse))
    {
        m_bVolumeKnobModify = false;
        LOG_INFO("Panel - Volume Value %: \"{0}\"", m_fVolumeValue * 100.0f);
    }

    if(m_bVolumeKnobModify)
    {
        const auto& nDeltaY = ImGui::GetMouseDragDelta().y;
        const auto& fVolumeRatio = 1.0f / g_fMaxTresholdVolumeDegrees;

        m_fVolumeValue = fVolumeRatio * m_fDegreesVolumeKnob;
        m_fDegreesVolumeKnob = std::abs(nDeltaY);

        if(m_fDegreesVolumeKnob >= g_fMaxTresholdVolumeDegrees)
        {
            m_fDegreesVolumeKnob = g_fMaxTresholdVolumeDegrees;
        }
    }

    /*Home Button*/
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

float fDegrees = 0.0f;

void Panel::OnDraw()
{
    const auto& rend = MainApp::GetInstance().ptrRend;

    /*Home Button*/
    rend->DrawPicture(m_homeButton.textureButton, m_homeButton.fX, m_homeButton.fY);

    /*Volume Button*/
    rend->DrawPicture(m_textureVolumeButton, g_fXVolumeButton, g_fYVolumeButton);
    rend->DrawPictureRotated(m_volumeKnobButton.textureButton, m_volumeKnobButton.fX, m_volumeKnobButton.fY, m_fDegreesVolumeKnob);
}
