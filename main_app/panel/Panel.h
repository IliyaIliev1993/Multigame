#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/font/Font.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/button/Button.h>

enum class EPanelInfoScenes
{
    eNoInfoScene = 0,
    eVolumeScene,
    eCreditScene
};

class Panel : public ITimer
{

private:

    /*Degrees Rotation Volume Knob*/
    float m_fDegreesVolumeKnob = 0.0f;

    /*Volume Valume 0.0f - 1.0f*/
    float m_fVolumeValue = 0.0f;

    /*Volume Percentage*/
    int m_nVolumePercentage = 0;

    /*Alpha channel info window*/
    float m_fAlphaInfoWindow = 0.0f;

    /*Textures Home Button pressed, released*/
    std::shared_ptr<Texture>m_textureHomeButton;
    std::shared_ptr<Texture>m_textureHomeButtonPressed;

    /*Textures Volume Button, knob volume*/
    std::shared_ptr<Texture>m_textureVolumeButton;
    std::shared_ptr<Texture>m_textureVolumeKnob;

    /*Texture info window*/
    std::shared_ptr<Texture>m_textureInfoWindow;

    /*Texture bet panel*/
    std::shared_ptr<Texture>m_texturePanel;
    std::shared_ptr<Texture>m_texturePanelPressed;

    /*Texture Exit Calculator Button*/
    std::shared_ptr<Texture>m_textureExitCalculator;
    std::shared_ptr<Texture>m_textureExitCalculatorPressed;

    /*Font Volume*/
    std::shared_ptr<Font>m_fontVolume;

    /*Home Button*/
    Button m_homeButton;

    /*Volume Knob Button*/
    Button m_volumeKnobButton;

    /*Credit Button - Field*/
    Button m_creditButton;

    /*Exit Calculator Button*/
    Button m_exitCalculatorButton;

    /*Holding the current Info scene drawed*/
    EPanelInfoScenes m_eInfoScene = EPanelInfoScenes::eNoInfoScene;

public:

    bool Init();
    bool Deinit();
    bool HandleEvent();
    void OnDraw();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
};