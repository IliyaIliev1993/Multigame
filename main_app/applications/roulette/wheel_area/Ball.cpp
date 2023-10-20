#include "Ball.h"

#include <math.h>
#include <main_app/MainApp.h>
#include <main_app/particle_system/Random.h>
#include <main_app/renderer/Renderer.h>
#include <debug/Logger.h>

constexpr unsigned int g_unTimerSpinning = 1;
constexpr unsigned int g_unTimerSpinningPeriod = 1;

constexpr unsigned int g_unTimerRotateWithWheel = 2;
constexpr unsigned int g_unTimerRotateWithWheelPeriod = 1;

constexpr unsigned int g_unRotatationCycles = 4;
constexpr unsigned int g_unRotationDuration = 7500;
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

constexpr float g_fUpperSideMiddleRingRadius = 215.0f;
constexpr float g_fDownerSideMiddleRingRadius = 208.0f;

constexpr float g_fMaxAlphaShadowBall = 0.4f;
constexpr float g_fMaxDifferenceYVectorShadowBall = 70.0f;
constexpr float g_fDegreesShadowBall = -40.0f;

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
    m_textureBallShadow = Texture::CreateTexture("../src/resources/roulette/wheel/ball_shadow.png");

    if (!m_textureBall->Load())
    {
        LOG_ERROR("Ball - Unable to load texture ball !");
        return false;
    }

    if (!m_textureBallShadow->Load())
    {
        LOG_ERROR("Ball - Unable to load texture ball shadow!");
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

void Ball::DrawShadow()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    float fAlphaFactor = g_fMaxAlphaShadowBall / g_fMaxDifferenceYVectorShadowBall;
    float fAlpha = g_fMaxAlphaShadowBall - (fAlphaFactor * (g_fYCenterWheelBall - m_fYBall));

    rend->SetColor(1.0f, 1.0f, 1.0f, fAlpha);

    const float fXShadow = m_fXPolarBall - (GameDefs::g_fWidthBallRoulette - 8.0f)  - ((g_fXCenterWheelBall - m_fYBall) * 4.0f);
    const float fYShadow = m_fYPolarBall - GameDefs::g_fHeightBallRoulette - ((g_fYCenterWheelBall - m_fYBall) * 2.0f);

    rend->DrawPictureRotated(m_textureBallShadow,
                             fXShadow,
                             fYShadow,
                             g_fDegreesShadowBall);

    rend->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Ball::Draw()
{
    const auto &rend = MainApp::GetInstance().ptrRend;

    /*Draw Shadow*/
    DrawShadow();

    /*Draw Ball*/
    rend->DrawPictureAroundPoint(m_textureBall, m_fXBall, m_fYBall, m_fDegreesBall, m_fDistanceFromWheelCenter);
}

void Ball::StartSpinning(const GameDefs::EWheelSectors& eWheelSectorToStopAt)
{
    const unsigned int unDurationRotation = g_unRotationDuration + Random::GetRandomNumber(-500.0f, 1000.0f);
    const float &fDeltaTime = MainApp::GetInstance().GetDeltaTime();
    const float fTargetSectorAngle = (eWheelSectorToStopAt * GameDefs::g_fAnglePerSector) + (m_fDegreesWheelRoulette - (90.0f - (GameDefs::g_fAnglePerSector / 2.0f)));
    const float fTargetSectorFutureAngle = fTargetSectorAngle + ((unDurationRotation / fDeltaTime) * 0.1);
    const float fStartPositionAnlge = g_fOriginStartPositionAngle - Random::GetRandomNumber(125.0f, 75.0f);
    const float fEndPositionAngle = (fTargetSectorFutureAngle - 360.0f) - 360.0f;

    LOG_INFO("Ball - StartPositionAngle: \"{0}\"", fStartPositionAnlge);
    LOG_INFO("Ball - EndPositionAngle: \"{0}\"", fEndPositionAngle);

    /*Start from hidden position*/
    m_fDistanceFromWheelCenter = g_fHiddenDistanceFormCenter;
    m_fDegreesBall = -90.0f;

    /*Start Throw the ball*/
    const unsigned int unDurationThrowBall = g_unThrowBallDuration + Random::GetRandomNumber(-50.0f, 100.0f);
    m_interpolatorThrowBall.Start(m_fDistanceFromWheelCenter, g_fHiddenDistanceFormCenter, g_fMaxDistanceFromCenter, Ease::SineOut, g_unThrowBallDuration);

    /*Start rotation of the ball*/
    m_interpolatorRotate.Start(m_fDegreesBall, fStartPositionAnlge, fEndPositionAngle, Ease::QuadraticOut, unDurationRotation);

    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerSpinning, g_unTimerSpinningPeriod);
    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerRotateWithWheel);

    m_eState = EBallStates::eRotateInTableOrbit;
    LOG_INFO("Ball - State: eRotateInTableOrbit");
}

void Ball::OnTick(unsigned int unID, unsigned int unTimes)
{
    if (unID == g_unTimerSpinning)
    {
        m_fCurrentSpeed = (m_fDegreesBallMemory - m_fDegreesBall) * 10.0f;
        m_fDegreesBallMemory = m_fDegreesBall;

        CheckForCollision();

        /*Here starts decrementing the distance and going to sector*/
        if (m_fDegreesBall <= (g_fAngleBeforeStartDecrementDistance + Random::GetRandomNumber(-180.0f, 0.0f)))
        {
            if (m_interpolatorDecrementDistance.GetState() == EInterpolatorStates::eInactive)
            {
                std::function<void()> endCallback = [this]()
                {
                    MainApp::GetInstance().ptrTimer->StopTimer(this, g_unTimerSpinning);
                    MainApp::GetInstance().ptrTimer->StartTimer(this, g_unTimerRotateWithWheel, g_unTimerRotateWithWheelPeriod);

                    m_eState = EBallStates::eStoppedAndRotateWithWheel;
                    m_afterSpinningStoppedCallback();
                    LOG_INFO("Ball - State: eStoppedAndRotateWithWheel");
                };

                m_interpolatorDecrementDistance.SetEndCallback(endCallback);
                /*Start decrement distance*/
                const unsigned int unDurationDecrementDistance = g_unDecrementDistanceDuration + Random::GetRandomNumber(-500.0f, 500.0f);
                m_interpolatorDecrementDistance.Start(m_fDistanceFromWheelCenter, g_fMaxDistanceFromCenter, g_fMinDistanceFromCenter, Ease::BounceOut, g_unDecrementDistanceDuration);

                m_eState = EBallStates::eGoingToSector;
                LOG_INFO("Ball - State: eGoingToSector");
            }
        }
    }

    if (unID == g_unTimerRotateWithWheel)
    {
        m_fDegreesBall += m_fSpeedWheelRoulette;
        m_fCurrentSpeed = (m_fDegreesBallMemory - m_fDegreesBall) * 10.0f;
        m_fDegreesBallMemory = m_fDegreesBall;

        /*Normalize when rotating normal*/
        if (m_fDegreesBall >= 360.0f)
        {
            m_fDegreesBall = 0.0f;
        }
    }
}

void Ball::CheckForCollision()
{
    /*Check for sector collision*/
    if (m_fDistanceFromWheelCenter < g_fDownerSideMiddleRingRadius &&
        m_fDistanceFromWheelCenter > g_fMinDistanceFromCenter)
    {
        const float fForceX = m_fCurrentSpeed * 3.0f;
        const float fForceY = -m_fCurrentSpeed * 8.0f;
        const float fDurationJump = m_fCurrentSpeed * 100.0f;
        const float fDurationBounce = m_fCurrentSpeed * 200.0f;

        StartCollision(fForceX,
                       fForceY,
                       fDurationJump,
                       fDurationBounce);
    }

    /*Check middle ring collision*/
    if (m_fDistanceFromWheelCenter >= g_fDownerSideMiddleRingRadius &&
        m_fDistanceFromWheelCenter <= g_fUpperSideMiddleRingRadius)
    {
        const float fForceFactorMiddleRingCollision = m_fCurrentSpeed * 2.0f;
        const float fDurationJump = 175.0f;
        const float fDurationBounce = 300.0f;
        StartCollision(-fForceFactorMiddleRingCollision,
                       -fForceFactorMiddleRingCollision,
                       fDurationJump,
                       fDurationBounce);
    }

    /*Check Rombus Collision*/
    const float fForceFactorRombusCollision = m_fCurrentSpeed * 5.0f;
    for (auto &rombusObject : g_arrRombusCollision)
    {
        auto &rombusLimits = rombusObject;
        if (m_fXPolarBall >= rombusLimits.at(eMinX) && m_fXPolarBall <= rombusLimits.at(eMaxX) &&
            m_fYPolarBall >= rombusLimits.at(eMinY) && m_fYPolarBall <= rombusLimits.at(eMaxY))
        {
            if (m_fDistanceFromWheelCenter <= g_fRombusRadiusCenter)
            {
                StartCollision(fForceFactorRombusCollision,
                               fForceFactorRombusCollision,
                               g_unRombusCollisionJumpUpDuration,
                               g_unRombusCollisionBounceDownDuration);
            }
            else
            {
                StartCollision(-fForceFactorRombusCollision,
                               -fForceFactorRombusCollision,
                               g_unRombusCollisionJumpUpDuration,
                               g_unRombusCollisionBounceDownDuration);
            }

            break;
        }
    }
}

void Ball::StartCollision(float fXForce, float fYForce, unsigned int unJumpDuration, unsigned int unBounceDuration)
{
    if (m_interpolatorCollisionJumpY.GetState() == EInterpolatorStates::eInactive &&
        m_interpolatorCollisionBounceY.GetState() == EInterpolatorStates::eInactive)
    {
        std::function<void()> endCallback = [this, unBounceDuration]()
        {
            m_interpolatorCollisionBounceY.Start(m_fYBall, m_fYBall, g_fYCenterWheelBall, Ease::BounceOut, unBounceDuration);
        };

        m_interpolatorCollisionJumpY.SetEndCallback(endCallback);
        m_interpolatorCollisionJumpY.Start(m_fYBall, m_fYBall, m_fYBall + fYForce, Ease::CircularOut, unJumpDuration);
        LOG_INFO("Ball - Collision with Forces (X): \"{0}\"", fXForce);
    }

    if (m_interpolatorCollisionJumpX.GetState() == EInterpolatorStates::eInactive &&
        m_interpolatorCollisionBounceX.GetState() == EInterpolatorStates::eInactive)
    {
        std::function<void()> endCallback = [this, unBounceDuration]()
        {
            m_interpolatorCollisionBounceX.Start(m_fXBall, m_fXBall, g_fXCenterWheelBall, Ease::BounceOut, unBounceDuration);
        };

        m_interpolatorCollisionJumpX.SetEndCallback(endCallback);
        m_interpolatorCollisionJumpX.Start(m_fXBall, m_fXBall, m_fXBall + fXForce, Ease::CircularOut, unJumpDuration);
        LOG_INFO("Ball - Collision with Forces (Y): \"{0}\"", fYForce);
    }
}

void Ball::SetDegreesRoulette(const float &fDegreesWheelRoulette)
{
    m_fDegreesWheelRoulette = fDegreesWheelRoulette;

    m_fXPolarBall = (m_fDistanceFromWheelCenter * cos(m_fDegreesBall * (M_PI / 180.0f))) + g_fXCenterWheelBall + (GameDefs::g_fWidthBallRoulette / 2.0f);
    m_fYPolarBall = (m_fDistanceFromWheelCenter * sin(m_fDegreesBall * (M_PI / 180.0f))) + g_fYCenterWheelBall + (GameDefs::g_fHeightBallRoulette / 2.0f);
}

void Ball::SetSpeedRoulette(const float &fSpeedWheelRoulette)
{
    m_fSpeedWheelRoulette = fSpeedWheelRoulette;
}

void Ball::SetAfterSpinningStoppedCallback(std::function<void()> &afterSpinningStoppedCallback)
{
    m_afterSpinningStoppedCallback = afterSpinningStoppedCallback;
}