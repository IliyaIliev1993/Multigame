#include "Wheel.h"

#include <main_app/MainApp.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/applications/roulette/GameDefinitions.h>
#include <debug/Logger.h>

constexpr float g_fXWheelTable = 0.0f;
constexpr float g_fYWheelTable = 0.0f;

constexpr float g_fXWheelOffset = 134.0f;
constexpr float g_fYWheelOffset = 134.0f;

constexpr float g_fSlowSpeedWheel = 0.1f;
constexpr float g_fFastSpeedWheel = 0.1f;

constexpr unsigned int g_unAccelerationSlowSpeedDuration = 2000;
constexpr unsigned int g_unAccelerationDecrementSpeedDuration = 3000;

constexpr unsigned int g_unTimerRotationWheel = 1;
constexpr unsigned int g_unTimerRotationWheelPeriod = 1;

bool Wheel::Init()
{
    m_textureWheelTable = Texture::CreateTexture("../src/resources/roulette/wheel/table_wheel.png");
    m_textureWheel = Texture::CreateTexture("../src/resources/roulette/wheel/wheel.png");

    if (!m_textureWheelTable->Load())
    {
        LOG_ERROR("Wheel - Unable to load texture table wheel !");
        return false;
    }

    if (!m_textureWheel->Load())
    {
        LOG_ERROR("Wheel - Unable to load texture wheel !");
        return false;
    }

    LOG_INFO("Wheel - Initialized ...");
    return true;
}

bool Wheel::Deinit()
{
    LOG_WARN("Wheel - Deinitialized ...");
    return true;
}

void Wheel::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    rend->DrawPicture(m_textureWheelTable, g_fXWheelTable, g_fYWheelTable);
    rend->DrawPictureRotated(m_textureWheel, g_fXWheelTable + g_fXWheelOffset, g_fYWheelTable + g_fYWheelOffset, m_fDegreesWheel);
}

void Wheel::StartSlowRotation()
{
    m_interpolatorAcceleration.Start(m_fSpeedWheel, 0.0f, g_fSlowSpeedWheel, Ease::SineIn, g_unAccelerationSlowSpeedDuration);
    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerRotationWheel, g_unTimerRotationWheelPeriod);
    LOG_INFO("Wheel - Start Slow Rotation");
}

void Wheel::StopSlowRotation()
{
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerRotationWheel);
    m_fSpeedWheel = 0.0f;
    LOG_INFO("Wheel - Stopped Slow Rotation");
}

void Wheel::StartFastRotation()
{
    m_interpolatorAcceleration.Start(m_fSpeedWheel, m_fSpeedWheel, g_fFastSpeedWheel, Ease::SineIn, g_unAccelerationSlowSpeedDuration);
    LOG_INFO("Wheel - Start Fast Rotation");
}

void Wheel::DecrementToSlowRotation()
{
    m_interpolatorAcceleration.Start(m_fSpeedWheel, g_fFastSpeedWheel, g_fSlowSpeedWheel, Ease::SineIn, g_unAccelerationDecrementSpeedDuration);
    LOG_INFO("Wheel - Decrement from Fast to Slow Rotation");
}

void Wheel::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerRotationWheel)
    {
        m_fDegreesWheel += m_fSpeedWheel;
        NormalizeAngle();

        /*Increment counter sector every time sector degrees change*/
        if (m_fDegreesWheel > (GameDefs::g_fAnglePerSector * m_unCounterSector))
        {
            ++m_unCounterSector;
        }
    }
}

void Wheel::NormalizeAngle()
{
    if (m_fDegreesWheel >= 360.0f)
    {
        m_fDegreesWheel = 0.0f;
        m_unCounterSector = 0;
    }
}

const float &Wheel::GetSpeed()
{
    return m_fSpeedWheel;
}

const float &Wheel::GetDegrees()
{
    return m_fDegreesWheel;
}