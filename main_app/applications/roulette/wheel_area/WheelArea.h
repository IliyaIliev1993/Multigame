#pragma once

#include "Wheel.h"
#include "Ball.h"

class WheelArea : public ITimer
{
private:
    /*Ball Object*/
    Ball m_Ball;

    /*Wheel Object*/
    Wheel m_Wheel;

    /*Callback, called after stop of the ball*/
    void AfterSpinningStopped();

    /*Callback, called after wheel stopped*/
    void AfterWheelStopped();

public:
    bool Init();
    bool Deinit();
    bool HandleEvent();
    void Draw();
    void StartSlowRotation();
    void StopRotation();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    /*Method called when need to start new spin*/
    void StartNewSpin();
};