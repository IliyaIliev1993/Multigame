#pragma once

#include <iomanip>

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

enum ECreditsCalculator
{
    eOne,
    eTwo,
    eFive,
    eTen,
    eTwenty,
    eFifthy,
    eHundred,
    eTwoHundreds,
    eFiveHundreds,
    eTotalCreditsCalculator
};

class Panel : public ITimer
{

private:
    /*Credit Available*/
    float m_fCreditAvailable = 0.0f;

    /*Degrees Rotation Volume Knob*/
    float m_fDegreesVolumeKnob = 0.0f;

    /*Volume Valume 0.0f - 1.0f*/
    float m_fVolumeValue = 0.0f;

    /*Volume Percentage*/
    int m_nVolumePercentage = 0;

    /*Alpha channel info window*/
    float m_fAlphaInfoWindow = 0.0f;

    /*String Credit Available*/
    std::string m_strCreditAvailable;

    /*Textures Home Button pressed, released*/
    std::shared_ptr<Texture> m_textureHomeButton;
    std::shared_ptr<Texture> m_textureHomeButtonPressed;

    /*Textures Volume Button, knob volume*/
    std::shared_ptr<Texture> m_textureVolumeButton;
    std::shared_ptr<Texture> m_textureVolumeKnob;

    /*Texture info window*/
    std::shared_ptr<Texture> m_textureInfoWindow;

    /*Texture panel*/
    std::shared_ptr<Texture> m_textureCreditPanel;
    std::shared_ptr<Texture> m_textureCreditPanelPressed;
    std::shared_ptr<Texture> m_textureBetPanel;
    std::shared_ptr<Texture> m_textureWinPanel;

    /*Texture Exit Calculator Button*/
    std::shared_ptr<Texture> m_textureExitCalculator;
    std::shared_ptr<Texture> m_textureExitCalculatorPressed;

    /*Textures Buttons Value Credit*/
    std::vector<std::shared_ptr<Texture>> m_vecTexturesButtonsValueCredit;
    std::vector<std::shared_ptr<Texture>> m_vecTexturesButtonsValueCreditPressed;

    /*Texture Reset Button*/
    std::shared_ptr<Texture> m_textureResetButton;
    std::shared_ptr<Texture> m_textureResetButtonPressed;

    /*Font Volume*/
    std::shared_ptr<Font> m_fontVolume;

    /*Home Button*/
    Button m_homeButton;

    /*Volume Knob Button*/
    Button m_volumeKnobButton;

    /*Credit Button - Field*/
    Button m_creditButton;

    /*Exit Calculator Button*/
    Button m_exitCalculatorButton;

    /*Buttons Value Credit*/
    std::vector<Button> m_vecButtonsValueCredit;

    /*Button Reset Credit*/
    Button m_resetCreditButton;

    /*Holding the current Info scene drawed*/
    EPanelInfoScenes m_eInfoScene = EPanelInfoScenes::eNoInfoScene;

    /*Method called when loading buttons, inserts elements in containers*/
    bool LoadCalculatorButtons();

    /*Method Draw Credit in base of lenght of digits*/
    void DrawDynamicTextCredit();

public:
    bool Init();
    bool Deinit();
    bool HandleEvent();
    void OnDraw();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    void AddCredit(float fCreditToAdd);
    void RemoveCredit(float fCreditToRemove);
    void ResetCredit();
};