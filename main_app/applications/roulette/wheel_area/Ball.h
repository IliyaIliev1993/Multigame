#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/interpolator/Interpolator.h>

class Ball : public ITimer
{

private:
    /*Degrees Ball*/
    float m_fDegreesBall = 0.0f;

    /*Speed Ball*/
    float m_fSpeedBall = 0.0f;

    /*Distance from wheel center*/
    float m_fDistanceFromWheelCenter = 0.0f;

    /*X Cordinate*/
    float m_fXBall = 0.0f;

    /*Y Coordinate*/
    float m_fYBall = 0.0f;

    /*Texture Ball*/
    std::shared_ptr<Texture> m_textureBall;

    /*Interpolator rotation*/
    Interpolator m_interpolatorRotate;

    /*Interpolator decrement distance, when rotation slows down*/
    Interpolator m_interpolatorDecrementDistance;

    /*Interpolator that simulate throw of the ball*/
    Interpolator m_interpolatorThrowBall;

    /*Interpolator collision, when collision is detected*/
    Interpolator m_interpolatorCollisionX;
    Interpolator m_interpolatorCollisionY;

    /*Check whenever there are some collisions*/
    void CheckForCollision();

    /*Starts collision effect*/
    void StartCollision();

public:
    bool Init();
    bool Deinit();
    void Draw();
    void StartSpinning();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
};