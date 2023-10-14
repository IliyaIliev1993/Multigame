#include "Ball.h"

#include <main_app/MainApp.h>
#include <main_app/particle_system/Random.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerSpinning = 1;
constexpr unsigned int g_unTimerSpinningPeriod = 1;

constexpr unsigned int g_unRotatationCycles = 4;
constexpr unsigned int g_unRotationDuration = 7000;
constexpr unsigned int g_unDecrementDistanceDuration = 3500;
constexpr unsigned int g_unThrowBallDuration = 200;

constexpr float g_fMinDistanceFromCenter = 182.0f;
constexpr float g_fMaxDistanceFromCenter = 380.0f;
constexpr float g_fHiddenDistanceFormCenter = 500.0f;

constexpr float g_fXCenterWheelBall = 421.0f;
constexpr float g_fYCenterWheelBall = 421.0f;

constexpr float g_fOriginStartPositionAngle = 360.0f * g_unRotatationCycles;
constexpr float g_fAngleBeforeStartDecrementDistance = 360.0f;

bool Ball::Init()
{
    m_textureBall = Texture::CreateTexture("../src/resources/roulette/wheel/ball.png");

    if (!m_textureBall->Load())
    {
        LOG_ERROR("Ball - Unable to load texture table ball !");
        return false;
    }

    /*Start from hidden position*/
    m_fXBall = g_fXCenterWheelBall;
    m_fYBall = g_fYCenterWheelBall;
    m_fDistanceFromWheelCenter = g_fHiddenDistanceFormCenter;
    m_fDegreesBall = -90.0f;

    LOG_INFO("Ball - Initialized ...");
    return true;
}

bool Ball::Deinit()
{
    LOG_WARN("Ball - Deinitialized ...");
    return true;
}

void Ball::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    rend->DrawPictureAroundPoint(m_textureBall, m_fXBall, m_fYBall, m_fDegreesBall, m_fDistanceFromWheelCenter);
}

void Ball::StartSpinning()
{
    const float fStartPositionAnlge = g_fOriginStartPositionAngle - Random::GetRandomNumber(125.0f, 75.0f);
    const float fEndPositionAngle = -90.0f;

    LOG_INFO("Ball - StartPositionAngle: \"{0}\"", fStartPositionAnlge);

    /*Start from hidden position*/
    m_fDistanceFromWheelCenter = g_fHiddenDistanceFormCenter;

    /*Start Throw the ball*/
    const unsigned int unDurationThrowBall = g_unThrowBallDuration + Random::GetRandomNumber(-50.0f, 100.0f);
    m_interpolatorThrowBall.Start(m_fDistanceFromWheelCenter, g_fHiddenDistanceFormCenter, g_fMaxDistanceFromCenter, Ease::SineOut, g_unThrowBallDuration);

    /*Start rotation of the ball*/
    const unsigned int unDurationRotation = g_unRotationDuration + Random::GetRandomNumber(-1500.0f, 2500.0f);
    m_interpolatorRotate.Start(m_fDegreesBall, fStartPositionAnlge, fEndPositionAngle, Ease::QuadraticOut, unDurationRotation);

    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerSpinning, g_unTimerSpinningPeriod);
}

void Ball::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerSpinning)
    {
        if (m_fDegreesBall <= g_fAngleBeforeStartDecrementDistance)
        {
            if (m_interpolatorDecrementDistance.GetState() == EInterpolatorStates::eInactive)
            {
                std::function<void()> endCallback = [this]()
                {
                    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerSpinning);
                };

                m_interpolatorDecrementDistance.SetEndCallback(endCallback);
                /*Start decrement distance*/
                const unsigned int unDurationDecrementDistance = g_unDecrementDistanceDuration + Random::GetRandomNumber(-500.0f, 1500.0f);
                m_interpolatorDecrementDistance.Start(m_fDistanceFromWheelCenter, g_fMaxDistanceFromCenter, g_fMinDistanceFromCenter, Ease::BounceOut, g_unDecrementDistanceDuration);
            }
        }
    }
}

void Ball::CheckForCollision()
{
}

void Ball::StartCollision()
{
    if (m_interpolatorCollisionY.GetState() == EInterpolatorStates::eInactive)
    {
        std::function<void()> endCallback = [this]()
        {
            m_interpolatorCollisionY.Start(m_fYBall, m_fYBall, g_fYCenterWheelBall, Ease::BounceOut, 1000);
        };

        m_interpolatorCollisionY.SetEndCallback(endCallback);
        m_interpolatorCollisionY.Start(m_fYBall, m_fYBall, m_fYBall + 50.0f, Ease::CircularOut, 250);
    }
}