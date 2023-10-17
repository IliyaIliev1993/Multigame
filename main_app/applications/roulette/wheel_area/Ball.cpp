#include "Ball.h"

#include <math.h>
#include <main_app/MainApp.h>
#include <main_app/particle_system/Random.h>
#include <main_app/renderer/Renderer.h>
#include <main_app/applications/roulette/GameDefinitions.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerSpinning = 1;
constexpr unsigned int g_unTimerSpinningPeriod = 1;

constexpr unsigned int g_unTimerRotateWithWheel = 2;
constexpr unsigned int g_unTimerRotateWithWheelPeriod = 1;

constexpr unsigned int g_unRotatationCycles = 4;
constexpr unsigned int g_unRotationDuration = 7000;
constexpr unsigned int g_unDecrementDistanceDuration = 3500;
constexpr unsigned int g_unThrowBallDuration = 200;

constexpr unsigned int g_unTotalRombusCollision = 8;
constexpr unsigned int g_unRombusCollisionJumpUpDuration = 1000;
constexpr unsigned int g_unRombusCollisionBounceDownDuration = 700;

constexpr float g_fMinDistanceFromCenter = 183.0f;
constexpr float g_fMaxDistanceFromCenter = 380.0f;
constexpr float g_fHiddenDistanceFormCenter = 500.0f;

constexpr float g_fXCenterWheelBall = 421.0f;
constexpr float g_fYCenterWheelBall = 421.0f;

constexpr float g_fOriginStartPositionAngle = 360.0f * g_unRotatationCycles;
constexpr float g_fAngleBeforeStartDecrementDistance = 360.0f;

constexpr float g_fRombusRadiusCenter = 330.0f;

const std::array<std::array<float, eTotalCollisionLimits>, g_unTotalRombusCollision> g_arrRombusCollision =
    {
        {
            /*Min X,  Max X,  Min Y,  Max Y*/ /*Starting Counter Clockwise*/
            {275.0f, 345.0f, 110.0f, 150.0f},
            {115.0f, 150.0f, 275.0f, 335.0f},
            {115.0f, 150.0f, 525.0f, 590.0f},
            {275.0f, 345.0f, 715.0f, 755.0f},
            {525.0f, 595.0f, 715.0f, 755.0f},
            {715.0f, 755.0f, 525.0f, 590.0f},
            {715.0f, 755.0f, 275.0f, 335.0f},
            {525.0f, 595.0f, 110.0f, 150.0f},
        }};

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
    m_eState = EBallStates::eHidden;

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
    m_fDegreesBall = -90.0f;

    /*Start Throw the ball*/
    const unsigned int unDurationThrowBall = g_unThrowBallDuration + Random::GetRandomNumber(-50.0f, 100.0f);
    m_interpolatorThrowBall.Start(m_fDistanceFromWheelCenter, g_fHiddenDistanceFormCenter, g_fMaxDistanceFromCenter, Ease::SineOut, g_unThrowBallDuration);

    /*Start rotation of the ball*/
    const unsigned int unDurationRotation = g_unRotationDuration + Random::GetRandomNumber(-1500.0f, 2500.0f);
    m_interpolatorRotate.Start(m_fDegreesBall, fStartPositionAnlge, fEndPositionAngle, Ease::QuadraticOut, unDurationRotation);

    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerSpinning, g_unTimerSpinningPeriod);
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerRotateWithWheel);

    m_eState = EBallStates::eRotateInTableOrbit;
}

void Ball::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerSpinning)
    {
        m_fCurrentSpeed = (m_fDegreesBallMemory - m_fDegreesBall) * 10.0f;
        m_fDegreesBallMemory = m_fDegreesBall;

        CheckForCollision();

        /*Here starts decrementing the distance and going to sector*/
        if (m_fDegreesBall <= g_fAngleBeforeStartDecrementDistance)
        {
            if (m_interpolatorDecrementDistance.GetState() == EInterpolatorStates::eInactive)
            {
                std::function<void()> endCallback = [this]()
                {
                    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerSpinning);
                    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerRotateWithWheel, g_unTimerRotateWithWheelPeriod);

                    m_eState = EBallStates::eStoppedAndRotateWithWheel;
                };

                m_interpolatorDecrementDistance.SetEndCallback(endCallback);
                /*Start decrement distance*/
                const unsigned int unDurationDecrementDistance = g_unDecrementDistanceDuration + Random::GetRandomNumber(-500.0f, 1500.0f);
                m_interpolatorDecrementDistance.Start(m_fDistanceFromWheelCenter, g_fMaxDistanceFromCenter, g_fMinDistanceFromCenter, Ease::BounceOut, g_unDecrementDistanceDuration);

                m_eState = EBallStates::eGoingToSector;
            }
        }
    }

    if(unID == g_unTimerRotateWithWheel)
    {
        m_fDegreesBall += m_fSpeedWheelRoulette;
        m_fCurrentSpeed = (m_fDegreesBallMemory - m_fDegreesBall) * 10.0f;
        m_fDegreesBallMemory = m_fDegreesBall;

        /*Normalize when rotating normal*/
        if(m_fDegreesBall >= 360.0f)
        {
            m_fDegreesBall = 0.0f;
        }
    }
}

void Ball::CheckForCollision()
{
    float fForceFactor = m_fCurrentSpeed * 5.0f;

    m_fXPolarBall = (m_fDistanceFromWheelCenter * cos(m_fDegreesBall * (M_PI / 180.0f))) + g_fXCenterWheelBall + (GameDefs::g_fWidthBallRoulette / 2.0f);
    m_fYPolarBall = (m_fDistanceFromWheelCenter * sin(m_fDegreesBall * (M_PI / 180.0f))) + g_fYCenterWheelBall + (GameDefs::g_fHeightBallRoulette / 2.0f);

    /*Check Rombus Collision*/
    for (auto &rombusObject : g_arrRombusCollision)
    {
        auto &rombusLimits = rombusObject;
        if (m_fXPolarBall >= rombusLimits.at(eMinX) && m_fXPolarBall <= rombusLimits.at(eMaxX) &&
            m_fYPolarBall >= rombusLimits.at(eMinY) && m_fYPolarBall <= rombusLimits.at(eMaxY))
        {
            if (m_fDistanceFromWheelCenter <= g_fRombusRadiusCenter)
            {
                StartCollision(fForceFactor, fForceFactor);
            }
            else
            {
                StartCollision(-fForceFactor, -fForceFactor);
            }

            break;
        }
    }
}

void Ball::StartCollision(float fXForce, float fYForce)
{
    LOG_INFO("Ball - Collision with Forces (X) - (Y): \"{0}\" - \"{1}\"", fXForce, fYForce);

    if (m_interpolatorCollisionJumpY.GetState() == EInterpolatorStates::eInactive)
    {
        std::function<void()> endCallback = [this]()
        {
            m_interpolatorCollisionBounceY.Start(m_fYBall, m_fYBall, g_fYCenterWheelBall, Ease::BounceOut, g_unRombusCollisionBounceDownDuration);
        };

        m_interpolatorCollisionJumpY.SetEndCallback(endCallback);
        m_interpolatorCollisionJumpY.Start(m_fYBall, m_fYBall, m_fYBall + fYForce, Ease::CircularOut, g_unRombusCollisionJumpUpDuration);
    }

    if (m_interpolatorCollisionJumpX.GetState() == EInterpolatorStates::eInactive)
    {
        std::function<void()> endCallback = [this]()
        {
            m_interpolatorCollisionBounceX.Start(m_fXBall, m_fXBall, g_fXCenterWheelBall, Ease::BounceOut, g_unRombusCollisionBounceDownDuration);
        };

        m_interpolatorCollisionJumpX.SetEndCallback(endCallback);
        m_interpolatorCollisionJumpX.Start(m_fXBall, m_fXBall, m_fXBall + fXForce, Ease::CircularOut, g_unRombusCollisionJumpUpDuration);
    }
}

void Ball::SetDegreesRoulette(const float &fDegreesWheelRoulette)
{
    m_fDegreesWheelRoulette = fDegreesWheelRoulette;
}

void Ball::SetSpeedRoulette(const float &fSpeedWheelRoulette)
{
    m_fSpeedWheelRoulette = fSpeedWheelRoulette;
}