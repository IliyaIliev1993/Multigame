#include "Panel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <main_app/MainApp.h>
#include <main_app/app_select/AppSelect.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerFadeMainWindow = 1;

constexpr float g_fXHomeButton = 0.0f;
constexpr float g_fYHomeButton = 920.0f;

constexpr float g_fXVolumeButton = 1720.0f;
constexpr float g_fYVolumeButton = 880.0f;
constexpr float g_fXVolumeKnobButton = 1765.0f;
constexpr float g_fYVolumeKnobButton = 925.0f;
constexpr float g_fXVolumeTextOffset = 105.0f;
constexpr float g_fYVolumeTextOffset = 45.0f;
constexpr float g_fXVolumePercentageOffset = 155.0f;
constexpr float g_fYVolumePercentageOffset = 310.0f;

constexpr float g_fXInfoWindow= 772.0f;
constexpr float g_fYInfoWindow = 260.0f;

constexpr float g_fXCreditPanel = 270.0f;
constexpr float g_fXBetPanel = 773.0f;
constexpr float g_fXWinPanel = 1280.0f;
constexpr float g_fYBetPanel = 928.0f;

constexpr float g_fMaxTresholdVolumeDegrees = 335.0f;

bool Panel::Init()
{
    m_textureHomeButton = Texture::CreateTexture("../src/resources/panel/home_button.png");
    m_textureHomeButtonPressed = Texture::CreateTexture("../src/resources/panel/home_button_pressed.png");
    m_textureVolumeButton = Texture::CreateTexture("../src/resources/panel/volume_button.png");
    m_textureVolumeKnob = Texture::CreateTexture("../src/resources/panel/knob_volume.png");
    m_textureInfoWindow = Texture::CreateTexture("../src/resources/panel/info_window.png");
    m_textureBetPanel = Texture::CreateTexture("../src/resources/panel/field.png");
    m_fontVolume = Font::CreateFont("../src/fonts/Nasa.ttf", 40);

    if(!m_textureHomeButton->Load())
    {
        LOG_ERROR("Panel - Unable to load texture home button!");
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

    if(!m_textureInfoWindow->Load())
    {
        LOG_ERROR("Panel - Unable to load texture info window!");
        return false;
    }

    if(!m_textureBetPanel->Load())
    {
        LOG_ERROR("Panel - Unable to load texture bet panel!");
        return false;
    }

    if(!m_fontVolume->LoadFont())
    {   
        LOG_ERROR("Panel - Unable to load font volume !");
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
        m_fAlphaInfoWindow = 1.0f;
    }
    if(m_volumeKnobButton.IsReleased(nXMouse, nYMouse))
    {
        m_bVolumeKnobModify = false;

        /*Start Timer effect fade info window*/
        MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerFadeMainWindow, 30);

        LOG_INFO("Panel - Volume Value %: \"{0}\"", m_fVolumeValue * 100.0f);
    }

    if(m_bVolumeKnobModify)
    {
        const auto& nDeltaY = ImGui::GetMouseDragDelta().y;
        const auto& fVolumeRatio = 1.0f / g_fMaxTresholdVolumeDegrees;

        m_fVolumeValue = fVolumeRatio * m_fDegreesVolumeKnob;
        m_nVolumePercentage = m_fVolumeValue * 100;
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

    /*Credit Panel*/
    rend->DrawPicture(m_textureBetPanel, g_fXCreditPanel, g_fYBetPanel);

    /*Bet Panel*/
    rend->DrawPicture(m_textureBetPanel, g_fXBetPanel, g_fYBetPanel);

    /*Win Panel*/
    rend->DrawPicture(m_textureBetPanel, g_fXWinPanel, g_fYBetPanel);

    /*Info Window*/
    if(m_fAlphaInfoWindow <= 0.0f)
    {
        return;
    }

    rend->SetColor(1.0f, 1.0f, 1.0f, m_fAlphaInfoWindow);
    rend->DrawPicture(m_textureInfoWindow, g_fXInfoWindow, g_fYInfoWindow);

    /*Volume Text*/
    rend->DrawText("VOLUME", m_fontVolume, g_fXInfoWindow + g_fXVolumeTextOffset, g_fYInfoWindow + g_fYVolumeTextOffset);
    rend->DrawText(std::to_string(m_nVolumePercentage) + " %", m_fontVolume, g_fXInfoWindow + g_fXVolumePercentageOffset, g_fYInfoWindow + g_fYVolumePercentageOffset, 1.3f);
    rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Panel::OnTick(unsigned int unID, unsigned int unTimes)
{
    if(unID == g_unTimerFadeMainWindow)
    {
        const float fStepDecrement = 0.1;
        m_fAlphaInfoWindow -= fStepDecrement;
        if(m_fAlphaInfoWindow <= 0.0f)
        {
            m_fAlphaInfoWindow = 0.0f;
            MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerFadeMainWindow);
        }
    }
}
