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

constexpr float g_fXInfoWindow = 772.0f;
constexpr float g_fYInfoWindow = 260.0f;

constexpr float g_fXCreditPanel = 270.0f;
constexpr float g_fXBetPanel = 773.0f;
constexpr float g_fXBetPanelDecrementButtonOffset = 0.0f;
constexpr float g_fXBetPanelIncrementButtonOffset = 272.0f;
constexpr float g_fXWinPanel = 1280.0f;
constexpr float g_fYBetPanel = 928.0f;

constexpr float g_fXCreditPanelTextTen = 395.0f;
constexpr float g_fXCreditPanelTextHundred = 385.0f;
constexpr float g_fXCreditPanelTextThousend = 370.0f;
constexpr float g_fXCreditPanelTextHundredThousend = 355.0f;
constexpr float g_fXCreditPanelTextMaxOffset = 345.0f;
constexpr float g_fYCreditPanelText = 1030.0f;

constexpr float g_fXBetPanelTextOffset = 135.0f;

constexpr float g_fMaxTresholdVolumeDegrees = 335.0f;

constexpr float g_fXAddCreditTextOffset = 80.0f;
constexpr float g_fXOffsetExitCalculatorButton = 58.0f;
constexpr float g_fYOffsetExitCalculatorButton = 469.0f;

constexpr float g_fXOneOffset = 19.0f;
constexpr float g_fYOneOffset = 77.0f;
constexpr float g_fXTwoOffset = 135.0f;
constexpr float g_fYTwoOffset = 77.0f;
constexpr float g_fXFiveOffset = 252.0f;
constexpr float g_fYFiveOffset = 77.0f;

constexpr float g_fXTenOffset = 19.0f;
constexpr float g_fYTenOffset = 191.0f;
constexpr float g_fXTwentyOffset = 135.0f;
constexpr float g_fYTwentyOffset = 191.0f;
constexpr float g_fXFifthyOffset = 252.0f;
constexpr float g_fYFifthyOffset = 191.0f;

constexpr float g_fXHundredOffset = 19.0f;
constexpr float g_fYHundredOffset = 305.0f;
constexpr float g_fXTwoHundredsOffset = 135.0f;
constexpr float g_fYTwoHundredsOffset = 305.0f;
constexpr float g_fXFiveHundredsOffset = 252.0f;
constexpr float g_fYFiveHundredsOffset = 305.0f;

constexpr float g_fXResetOffset = 115.0f;
constexpr float g_fYResetOffset = 410.0f;

bool Panel::Init()
{
    m_textureHomeButton = Texture::CreateTexture("../src/resources/panel/home_button.png");
    m_textureHomeButtonPressed = Texture::CreateTexture("../src/resources/panel/home_button_pressed.png");
    m_textureVolumeButton = Texture::CreateTexture("../src/resources/panel/volume_button.png");
    m_textureVolumeKnob = Texture::CreateTexture("../src/resources/panel/knob_volume.png");
    m_textureInfoWindow = Texture::CreateTexture("../src/resources/panel/info_window.png");
    m_textureCreditPanel = Texture::CreateTexture("../src/resources/panel/credit_field.png");
    m_textureCreditPanelPressed = Texture::CreateTexture("../src/resources/panel/credit_field_pressed.png");
    m_textureCreditPanelPressToAdd = Texture::CreateTexture("../src/resources/panel/credit_field_press_to_add.png");
    m_textureBetPanel = Texture::CreateTexture("../src/resources/panel/bet_field.png");
    m_textureBetPanelIncrement = Texture::CreateTexture("../src/resources/panel/increment.png");
    m_textureBetPanelIncrementPressed = Texture::CreateTexture("../src/resources/panel/increment_pressed.png");
    m_textureBetPanelDecrement = Texture::CreateTexture("../src/resources/panel/decrement.png");
    m_textureBetPanelDecrementPressed = Texture::CreateTexture("../src/resources/panel/decrement_pressed.png");
    m_textureWinPanel = Texture::CreateTexture("../src/resources/panel/win_field.png");
    m_textureExitCalculator = Texture::CreateTexture("../src/resources/panel/calculator/exit.png");
    m_textureExitCalculatorPressed = Texture::CreateTexture("../src/resources/panel/calculator/exit_pressed.png");
    m_textureResetButton = Texture::CreateTexture("../src/resources/panel/calculator/reset_button.png");
    m_textureResetButtonPressed = Texture::CreateTexture("../src/resources/panel/calculator/reset_button_pressed.png");

    m_fontVolume = Font::CreateFont("../src/fonts/Nasa.ttf", 40);

    if (!m_textureHomeButton->Load())
    {
        LOG_ERROR("Panel - Unable to load texture home button!");
        return false;
    }

    if (!m_textureHomeButtonPressed->Load())
    {
        LOG_ERROR("Panel - Unable to load texture home button pressed!");
        return false;
    }

    if (!m_textureVolumeButton->Load())
    {
        LOG_ERROR("Panel - Unable to load texture volume button!");
        return false;
    }

    if (!m_textureVolumeKnob->Load())
    {
        LOG_ERROR("Panel - Unable to load texture volume knob!");
        return false;
    }

    if (!m_textureInfoWindow->Load())
    {
        LOG_ERROR("Panel - Unable to load texture info window!");
        return false;
    }

    if (!m_textureCreditPanel->Load())
    {
        LOG_ERROR("Panel - Unable to load texture credit panel!");
        return false;
    }

    if (!m_textureCreditPanelPressed->Load())
    {
        LOG_ERROR("Panel - Unable to load texture credit panel pressed!");
        return false;
    }

    if (!m_textureCreditPanelPressToAdd->Load())
    {
        LOG_ERROR("Panel - Unable to load texture credit panel press to add!");
        return false;
    }

    if (!m_textureBetPanel->Load())
    {
        LOG_ERROR("Panel - Unable to load texture bet panel!");
        return false;
    }

    if (!m_textureBetPanelIncrement->Load())
    {
        LOG_ERROR("Panel - Unable to load texture bet panel increment!");
        return false;
    }

    if (!m_textureBetPanelIncrementPressed->Load())
    {
        LOG_ERROR("Panel - Unable to load texture bet panel increment pressed!");
        return false;
    }

    if (!m_textureBetPanelDecrement->Load())
    {
        LOG_ERROR("Panel - Unable to load texture bet panel decrement!");
        return false;
    }

    if (!m_textureBetPanelDecrementPressed->Load())
    {
        LOG_ERROR("Panel - Unable to load texture bet panel decrement pressed!");
        return false;
    }

    if (!m_textureWinPanel->Load())
    {
        LOG_ERROR("Panel - Unable to load texture winn panel!");
        return false;
    }

    if (!m_textureExitCalculator->Load())
    {
        LOG_ERROR("Panel - Unable to load texture exit calculator!");
        return false;
    }

    if (!m_textureExitCalculatorPressed->Load())
    {
        LOG_ERROR("Panel - Unable to load texture exit calculator pressed!");
        return false;
    }

    if (!m_textureResetButton->Load())
    {
        LOG_ERROR("Panel - Unable to load texture reset button!");
        return false;
    }

    if (!m_textureResetButtonPressed->Load())
    {
        LOG_ERROR("Panel - Unable to load texture reset button pressed!");
        return false;
    }

    if (!m_fontVolume->LoadFont())
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

    m_creditButton.textureButton = m_textureCreditPanel;
    m_creditButton.fX = g_fXCreditPanel;
    m_creditButton.fY = g_fYBetPanel;
    m_creditButton.fontButton = m_fontVolume;

    m_betButton.textureButton = m_textureBetPanel;
    m_betButton.fX = g_fXBetPanel;
    m_betButton.fY = g_fYBetPanel;

    m_decrementBetButton.textureButton = m_textureBetPanelDecrement;
    m_decrementBetButton.fX = g_fXBetPanel + g_fXBetPanelDecrementButtonOffset;
    m_decrementBetButton.fY = g_fYBetPanel;

    m_incrementBetButton.textureButton = m_textureBetPanelIncrement;
    m_incrementBetButton.fX = g_fXBetPanel + g_fXBetPanelIncrementButtonOffset;
    m_incrementBetButton.fY = g_fYBetPanel;

    m_exitCalculatorButton.textureButton = m_textureExitCalculator;
    m_exitCalculatorButton.fX = g_fXOffsetExitCalculatorButton + g_fXInfoWindow;
    m_exitCalculatorButton.fY = g_fYOffsetExitCalculatorButton + g_fYInfoWindow;

    m_resetCreditButton.textureButton = m_textureResetButton;
    m_resetCreditButton.fX = g_fXInfoWindow + g_fXResetOffset;
    m_resetCreditButton.fY = g_fYInfoWindow + g_fYResetOffset;

    if (!LoadCalculatorButtons())
    {
        return false;
    }

    std::string strFloatToString = std::to_string(m_fCreditAvailable);
    m_strCreditAvailable = strFloatToString.substr(0, strFloatToString.find(".") + 3);

    strFloatToString = std::to_string(m_fCurrentBet);
    m_strCurrentBet = strFloatToString.substr(0, strFloatToString.find(".") + 3);

    LOG_INFO("Panel - Initialized ...");
    return true;
}

bool Panel::LoadCalculatorButtons()
{
    const unsigned int unTotalElements = ECreditsCalculator::eTotalCreditsCalculator;

    m_vecTexturesButtonsValueCredit.reserve(unTotalElements);
    m_vecTexturesButtonsValueCreditPressed.reserve(unTotalElements);
    m_vecButtonsValueCredit.reserve(unTotalElements);

    for (auto i = 0; i < unTotalElements; ++i)
    {
        std::string strButton = "button_1";
        Button buttonCredit;

        switch (i)
        {
        case ECreditsCalculator::eOne:
        {
            strButton = "button_1";
            buttonCredit.fX = g_fXInfoWindow + g_fXOneOffset;
            buttonCredit.fY = g_fYInfoWindow + g_fYOneOffset;
            buttonCredit.fValue = 1.00f;
        }
        break;

        case ECreditsCalculator::eTwo:
        {
            strButton = "button_2";
            buttonCredit.fX = g_fXInfoWindow + g_fXTwoOffset;
            buttonCredit.fY = g_fYInfoWindow + g_fYTwoOffset;
            buttonCredit.fValue = 2.00f;
        }
        break;

        case ECreditsCalculator::eFive:
        {
            strButton = "button_5";
            buttonCredit.fX = g_fXInfoWindow + g_fXFiveOffset;
            buttonCredit.fY = g_fYInfoWindow + g_fYFiveOffset;
            buttonCredit.fValue = 5.00f;
        }
        break;

        case ECreditsCalculator::eTen:
        {
            strButton = "button_10";
            buttonCredit.fX = g_fXInfoWindow + g_fXTenOffset;
            buttonCredit.fY = g_fYInfoWindow + g_fYTenOffset;
            buttonCredit.fValue = 10.0f;
        }
        break;

        case ECreditsCalculator::eTwenty:
        {
            strButton = "button_20";
            buttonCredit.fX = g_fXInfoWindow + g_fXTwentyOffset;
            buttonCredit.fY = g_fYInfoWindow + g_fYTwentyOffset;
            buttonCredit.fValue = 20.0f;
        }
        break;

        case ECreditsCalculator::eFifthy:
        {
            strButton = "button_50";
            buttonCredit.fX = g_fXInfoWindow + g_fXFifthyOffset;
            buttonCredit.fY = g_fYInfoWindow + g_fYFifthyOffset;
            buttonCredit.fValue = 50.0f;
        }
        break;

        case ECreditsCalculator::eHundred:
        {
            strButton = "button_100";
            buttonCredit.fX = g_fXInfoWindow + g_fXHundredOffset;
            buttonCredit.fY = g_fYInfoWindow + g_fYHundredOffset;
            buttonCredit.fValue = 100.0f;
        }
        break;

        case ECreditsCalculator::eTwoHundreds:
        {
            strButton = "button_200";
            buttonCredit.fX = g_fXInfoWindow + g_fXTwoHundredsOffset;
            buttonCredit.fY = g_fYInfoWindow + g_fYTwoHundredsOffset;
            buttonCredit.fValue = 200.0f;
        }
        break;

        case ECreditsCalculator::eFiveHundreds:
        {
            strButton = "button_500";
            buttonCredit.fX = g_fXInfoWindow + g_fXFiveHundredsOffset;
            buttonCredit.fY = g_fYInfoWindow + g_fYFiveHundredsOffset;
            buttonCredit.fValue = 500.0f;
        }
        break;

        default:
            break;
        }

        const std::string strPath = "../src/resources/panel/calculator/";
        const std::string strButtonToLoad = strPath + strButton + ".png";
        const std::string strButtonToLoadPressed = strPath + strButton + "_pressed.png";

        std::shared_ptr<Texture> textureButton = Texture::CreateTexture(strButtonToLoad);
        std::shared_ptr<Texture> textureButtonPressed = Texture::CreateTexture(strButtonToLoadPressed);

        if (!textureButton->Load())
        {
            LOG_ERROR("Panel - Unable to load texture \"{0}\"!", strButtonToLoad);
            return false;
        }

        if (!textureButtonPressed->Load())
        {
            LOG_ERROR("Panel - Unable to load texture \"{0}\"!", strButtonToLoadPressed);
            return false;
        }

        buttonCredit.textureButton = textureButton;

        m_vecTexturesButtonsValueCredit.emplace_back(textureButton);
        m_vecTexturesButtonsValueCreditPressed.emplace_back(textureButtonPressed);
        m_vecButtonsValueCredit.emplace_back(buttonCredit);
    }

    return true;
}

bool Panel::Deinit()
{
    LOG_INFO("Panel - Deinitialized ...");
    return true;
}

bool Panel::HandleEvent()
{
    const auto &nXMouse = ImGui::GetMousePos().x;
    const auto &nYMouse = ImGui::GetMousePos().y;

    if (m_eInfoScene == EPanelInfoScenes::eCreditScene)
    {
        /*Credit Buttons*/
        for (unsigned int i = 0; i < m_vecButtonsValueCredit.size(); ++i)
        {
            auto &button = m_vecButtonsValueCredit[i];
            auto &texture = m_vecTexturesButtonsValueCredit[i];
            auto &texturePressed = m_vecTexturesButtonsValueCreditPressed[i];

            if (button.IsPressed(nXMouse, nYMouse))
            {
                button.textureButton = texturePressed;
                LOG_INFO("Panel - Pressed \"{0}\" credit", button.fValue);

                AddCredit(button.fValue);
                return true;
            }
            else if (button.IsReleased(nXMouse, nYMouse))
            {
                button.textureButton = texture;
            }
        }

        /*Reset Credit Button*/
        if (m_resetCreditButton.IsPressAndHold(nXMouse, nYMouse))
        {
            m_resetCreditButton.textureButton = m_textureResetButtonPressed;
            return true;
        }
        else
        {
            m_resetCreditButton.textureButton = m_textureResetButton;
            if (m_resetCreditButton.IsReleased(nXMouse, nYMouse))
            {
                ResetCredit();
                return true;
            }
        }

        /*Exit Calculator Button*/
        if (m_exitCalculatorButton.IsPressAndHold(nXMouse, nYMouse))
        {
            m_exitCalculatorButton.textureButton = m_textureExitCalculatorPressed;
            return true;
        }
        else
        {
            m_exitCalculatorButton.textureButton = m_textureExitCalculator;

            /*When button relaesed, exit from calculator scene*/
            if (m_exitCalculatorButton.IsReleased(nXMouse, nYMouse))
            {
                /*Start Timer effect fade info window*/
                MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerFadeMainWindow, 1);
                return true;
            }
        }

        return true;
    }

    /*Credit Button - Field*/
    if (m_creditButton.IsPressAndHold(nXMouse, nYMouse))
    {
        m_creditButton.textureButton = m_textureCreditPanelPressed;
        return true;
    }
    else
    {

        /*When button relaesed, activate calculator scene*/
        if (m_creditButton.IsReleased(nXMouse, nYMouse))
        {
            m_eInfoScene = EPanelInfoScenes::eCreditScene;
            m_fAlphaInfoWindow = 1.0f;

            return true;
        }

        /*Hover Effect*/
        if (m_eInfoScene == EPanelInfoScenes::eNoInfoScene &&
            m_creditButton.IsHovered(nXMouse, nYMouse))
        {
            m_creditButton.textureButton = m_textureCreditPanelPressToAdd;
        }
        else
        {
            m_creditButton.textureButton = m_textureCreditPanel;
        }
    }

    /*Bet Button - Field*/
    if (m_betButton.IsHovered(nXMouse, nYMouse))
    {
        /*Bet increment/decrement*/
        const float fBetModifier = 0.50f;

        /*Decremenet Button*/
        if (m_decrementBetButton.IsPressAndHold(nXMouse, nYMouse))
        {
            m_decrementBetButton.textureButton = m_textureBetPanelDecrementPressed;
            return true;
        }
        else
        {
            m_decrementBetButton.textureButton = m_textureBetPanelDecrement;

            /*When button relaesed, decrement bet*/
            if (m_decrementBetButton.IsReleased(nXMouse, nYMouse))
            {
                m_fCurrentBet -= fBetModifier;
                if (m_fCurrentBet <= GameDefs::g_fMinBet)
                {
                    m_fCurrentBet = GameDefs::g_fMinBet;
                }

                std::string strFloatToString = std::to_string(m_fCurrentBet);
                m_strCurrentBet = strFloatToString.substr(0, strFloatToString.find(".") + 3);

                return true;
            }
        }

        /*Increment Button*/
        if (m_incrementBetButton.IsPressAndHold(nXMouse, nYMouse))
        {
            m_incrementBetButton.textureButton = m_textureBetPanelIncrementPressed;
            return true;
        }
        else
        {
            m_incrementBetButton.textureButton = m_textureBetPanelIncrement;

            /*When button relaesed, increment bet*/
            if (m_incrementBetButton.IsReleased(nXMouse, nYMouse))
            {
                m_fCurrentBet += fBetModifier;
                if (m_fCurrentBet >= GameDefs::g_fMaxBet)
                {
                    m_fCurrentBet = GameDefs::g_fMaxBet;
                }

                std::string strFloatToString = std::to_string(m_fCurrentBet);
                m_strCurrentBet = strFloatToString.substr(0, strFloatToString.find(".") + 3);

                return true;
            }
        }
    }

    /*Volume Button*/
    if (m_volumeKnobButton.IsPressed(nXMouse, nYMouse))
    {
        m_eInfoScene = EPanelInfoScenes::eVolumeScene;
        m_fAlphaInfoWindow = 1.0f;
    }
    else if (m_volumeKnobButton.IsReleased(nXMouse, nYMouse))
    {
        /*Start Timer effect fade info window*/
        MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerFadeMainWindow, 1);
        LOG_INFO("Panel - Volume Value %: \"{0}\"", m_fVolumeValue * 100.0f);
    }

    if (m_eInfoScene == EPanelInfoScenes::eVolumeScene)
    {
        if (m_volumeKnobButton.bIsClicked)
        {
            const auto &nDeltaY = ImGui::GetMouseDragDelta().y;
            const auto &fVolumeRatio = 1.0f / g_fMaxTresholdVolumeDegrees;

            m_fVolumeValue = fVolumeRatio * m_fDegreesVolumeKnob;
            m_nVolumePercentage = m_fVolumeValue * 100;
            m_fDegreesVolumeKnob = std::abs(nDeltaY);

            if (m_fDegreesVolumeKnob >= g_fMaxTresholdVolumeDegrees)
            {
                m_fDegreesVolumeKnob = g_fMaxTresholdVolumeDegrees;
            }

            return true;
        }

        return true;
    }

    /*Home Button*/
    if (m_homeButton.IsPressAndHold(nXMouse, nYMouse))
    {
        m_homeButton.textureButton = m_textureHomeButtonPressed;
        return true;
    }
    else
    {
        m_homeButton.textureButton = m_textureHomeButton;

        /*When button relaesed, request transition to app select*/
        if (m_homeButton.IsReleased(nXMouse, nYMouse))
        {
            MainApp::GetInstance().ptrAppSelect->RequestTransition(EApps::eAppSelect);
            return true;
        }
    }

    return false;
}

bool Panel::CanStartNewGame()
{
    if((m_fCreditAvailable + m_fCurrentWin) >= m_fCurrentBet)
    {
        return true;
    }

    LOG_ERROR("Panel - Cannot Start New Game! Insufficient credit !");

    return false;
}

void Panel::DrawCreditPanelButton()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    rend->DrawPicture(m_creditButton.textureButton, m_creditButton.fX, m_creditButton.fY);
    DrawDynamicTextCredit();
}

void Panel::DrawBetPanel()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    rend->DrawPicture(m_betButton.textureButton, m_betButton.fX, m_betButton.fY);
    rend->DrawText(m_strCurrentBet, m_fontVolume, g_fXBetPanel + g_fXBetPanelTextOffset, g_fYCreditPanelText, 1.5f);

    if (m_betButton.bIsHovered)
    {
        rend->DrawPicture(m_decrementBetButton.textureButton, m_decrementBetButton.fX, m_decrementBetButton.fY);
        rend->DrawPicture(m_incrementBetButton.textureButton, m_incrementBetButton.fX, m_incrementBetButton.fY);
    }
}

void Panel::OnDraw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Home Button*/
    rend->DrawPicture(m_homeButton.textureButton, m_homeButton.fX, m_homeButton.fY);

    /*Volume Button*/
    rend->DrawPicture(m_textureVolumeButton, g_fXVolumeButton, g_fYVolumeButton);
    rend->DrawPictureRotated(m_volumeKnobButton.textureButton, m_volumeKnobButton.fX, m_volumeKnobButton.fY, m_fDegreesVolumeKnob);

    /*Credit Button - Panel*/
    DrawCreditPanelButton();

    /*Bet Panel*/
    DrawBetPanel();

    /*Win Panel*/
    rend->DrawPicture(m_textureWinPanel, g_fXWinPanel, g_fYBetPanel);

    /*Info Calculator Window*/
    if (m_eInfoScene == EPanelInfoScenes::eCreditScene)
    {
        rend->SetColor(1.0f, 1.0f, 1.0f, m_fAlphaInfoWindow);
        rend->DrawPicture(m_textureInfoWindow, g_fXInfoWindow, g_fYInfoWindow);

        /*Credit Text*/
        rend->DrawText("ADD CREDIT", m_fontVolume, g_fXInfoWindow + g_fXAddCreditTextOffset, g_fYInfoWindow + g_fYVolumeTextOffset);

        /*Credit Buttons*/
        for (const auto &button : m_vecButtonsValueCredit)
        {
            rend->DrawPicture(button.textureButton, button.fX, button.fY);
        }

        /*Reset Button*/
        rend->DrawPicture(m_resetCreditButton.textureButton, m_resetCreditButton.fX, m_resetCreditButton.fY);

        /*Exit Button*/
        rend->DrawPicture(m_exitCalculatorButton.textureButton, m_exitCalculatorButton.fX, m_exitCalculatorButton.fY);
        rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    /*Info Volume Window*/
    else if (m_eInfoScene == EPanelInfoScenes::eVolumeScene)
    {
        rend->SetColor(1.0f, 1.0f, 1.0f, m_fAlphaInfoWindow);
        rend->DrawPicture(m_textureInfoWindow, g_fXInfoWindow, g_fYInfoWindow);

        /*Volume Text*/
        rend->DrawText("VOLUME", m_fontVolume, g_fXInfoWindow + g_fXVolumeTextOffset, g_fYInfoWindow + g_fYVolumeTextOffset);
        rend->DrawText(std::to_string(m_nVolumePercentage) + " %", m_fontVolume, g_fXInfoWindow + g_fXVolumePercentageOffset, g_fYInfoWindow + g_fYVolumePercentageOffset, 1.3f);
        rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

void Panel::DrawDynamicTextCredit()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    const auto &nLenghtOfString = m_strCreditAvailable.length();
    float fXDynamic = g_fXCreditPanelTextTen;
    /*0 - 9*/
    if (nLenghtOfString <= 4)
    {
        fXDynamic = g_fXCreditPanelTextTen;
    }
    /*10 - 99*/
    else if (nLenghtOfString == 5)
    {
        fXDynamic = g_fXCreditPanelTextHundred;
    }
    /*100 - 999*/
    else if (nLenghtOfString == 6)
    {
        fXDynamic = g_fXCreditPanelTextThousend;
    }
    else if (nLenghtOfString == 7)
    {
        fXDynamic = g_fXCreditPanelTextHundredThousend;
    }
    else if (nLenghtOfString >= 8)
    {
        fXDynamic = g_fXCreditPanelTextMaxOffset;
    }

    /*When Hovered no need to draw credit available*/
    if (m_creditButton.bIsHovered)
    {
        return;
    }
    rend->DrawText(m_strCreditAvailable, m_fontVolume, fXDynamic, g_fYCreditPanelText, 1.5f);
}

void Panel::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerFadeMainWindow)
    {
        const float fStepDecrement = 0.05;
        m_fAlphaInfoWindow -= fStepDecrement;
        if (m_fAlphaInfoWindow <= 0.0f)
        {
            m_eInfoScene = EPanelInfoScenes::eNoInfoScene;
            m_fAlphaInfoWindow = 0.0f;
            MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerFadeMainWindow);
        }
    }
}

void Panel::AddCredit(float fCreditToAdd)
{
    if (fCreditToAdd <= 0.0f)
    {
        LOG_CRITICAL("Panel - Cannot add zero or negative credit !");
        return;
    }

    LOG_INFO("Panel - Credit BEFORE adding -> \"{0}\"", m_fCreditAvailable);
    LOG_INFO("Panel - Credit to be added -> \"{0}\"", fCreditToAdd);

    m_fCreditAvailable += fCreditToAdd;

    LOG_INFO("Panel - Credit AFTER adding -> \"{0}\"", m_fCreditAvailable);

    std::string strFloatToString = std::to_string(m_fCreditAvailable);
    m_strCreditAvailable = strFloatToString.substr(0, strFloatToString.find(".") + 3);
}

void Panel::RemoveCredit(float fCreditToBeRemoved)
{
    if (fCreditToBeRemoved <= 0.0f)
    {
        LOG_CRITICAL("Panel - Cannot remove zero or negative credit !");
        return;
    }

    LOG_INFO("Panel - Credit BEFORE remove -> \"{0}\"", m_fCreditAvailable);
    LOG_INFO("Panel - Credit to be removed -> \"{0}\"", fCreditToBeRemoved);

    m_fCreditAvailable -= fCreditToBeRemoved;

    LOG_INFO("Panel - Credit AFTER remove -> \"{0}\"", m_fCreditAvailable);

    std::string strFloatToString = std::to_string(m_fCreditAvailable);
    m_strCreditAvailable = strFloatToString.substr(0, strFloatToString.find(".") + 3);
}

void Panel::DecrementCreditWithBet()
{
    RemoveCredit(m_fCurrentBet);
}

void Panel::ResetCredit()
{
    m_fCreditAvailable = 0.0f;

    LOG_INFO("Panel - Credit reset to -> \"{0}\"", m_fCreditAvailable);

    std::string strFloatToString = std::to_string(m_fCreditAvailable);
    m_strCreditAvailable = strFloatToString.substr(0, strFloatToString.find(".") + 3);
}
