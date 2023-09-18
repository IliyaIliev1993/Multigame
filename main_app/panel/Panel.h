#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/button/Button.h>

class Panel : public ITimer
{

private:

    /*Degrees Rotation Volume Knob*/
    float m_fDegreesVolumeKnob = 0.0f;

    /*Volume Valume 0.0f - 1.0f*/
    float m_fVolumeValue = 0.0f;

    /*Alpha channel info window*/
    float m_fAlphaInfoWindow = 0.0f;

    /*Flag modification Volume Knob*/
    bool m_bVolumeKnobModify = false;

    /*Textures Home Button pressed, released*/
    std::shared_ptr<Texture>m_textureHomeButton;
    std::shared_ptr<Texture>m_textureHomeButtonPressed;

    /*Textures Volume Button, knob volume*/
    std::shared_ptr<Texture>m_textureVolumeButton;
    std::shared_ptr<Texture>m_textureVolumeKnob;

    /*Texture info window*/
    std::shared_ptr<Texture>m_textureInfoWindow;

    /*Home Button*/
    Button m_homeButton;

    /*Volume Knob Button*/
    Button m_volumeKnobButton;

public:

    bool Init();
    bool Deinit();
    bool HandleEvent();
    void OnDraw();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
};