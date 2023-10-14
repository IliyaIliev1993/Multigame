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

public:

    bool Init();
    bool Deinit();
    bool HandleEvent();
    void Draw();
    void StartSlowRotation();
    void StopSlowRotation();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
};