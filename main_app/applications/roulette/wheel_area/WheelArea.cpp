#include "WheelArea.h"

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr float g_fXWheelTable = 0.0f;
constexpr float g_fYWheelTable = 0.0f;

constexpr float g_fXWheelOffset = 134.0f;
constexpr float g_fYWheelOffset = 134.0f;

constexpr float g_fSlowSpeedWheel = 0.1f;

constexpr unsigned int g_unAccelerationSlowSpeedDuration = 2000;

constexpr unsigned int g_unTimerRotationWheel = 1;
constexpr unsigned int g_unTimerRotationWheelPeriod = 1;

bool WheelArea::Init()
{
    m_textureWheelTable = Texture::CreateTexture("../src/resources/roulette/wheel/table_wheel.png");
    m_textureWheel = Texture::CreateTexture("../src/resources/roulette/wheel/wheel.png");

    if (!m_textureWheelTable->Load())
    {
        LOG_ERROR("WheelArea - Unable to load texture table wheel !");
        return false;
    }

    if (!m_textureWheel->Load())
    {
        LOG_ERROR("WheelArea - Unable to load texture wheel !");
        return false;
    }

    LOG_INFO("Wheel Area - Initialized ...");
    return true;
}

bool WheelArea::Deinit()
{
    LOG_WARN("Wheel Area - Deinitialized ...");
    return true;
}

void WheelArea::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;
    
    rend->DrawPicture(m_textureWheelTable, g_fXWheelTable, g_fYWheelTable);
    rend->DrawPictureRotated(m_textureWheel, g_fXWheelTable + g_fXWheelOffset, g_fYWheelTable + g_fYWheelOffset, m_fDegreesWheel);
}

void WheelArea::StartSlowRotation()
{
    m_interpolatorAcceleration.Start(m_fSpeedWheel, 0.0f, g_fSlowSpeedWheel, Ease::SineIn, g_unAccelerationSlowSpeedDuration);
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerRotationWheel, g_unTimerRotationWheelPeriod);
}

void WheelArea::StopSlowRotation()
{
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerRotationWheel);
}

void WheelArea::OnTick(unsigned int unID, unsigned int unTimes)
{
    if(unID == g_unTimerRotationWheel)
    {
        m_fDegreesWheel += m_fSpeedWheel;
        NormalizeAngle();
    }
}

void WheelArea::NormalizeAngle()
{
    if(m_fDegreesWheel >= 360.0f)
    {
        m_fDegreesWheel = 0.0f;
    }
}