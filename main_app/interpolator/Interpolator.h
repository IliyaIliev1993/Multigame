#pragma once
#include "Easing.h"

#include <main_app/timer/TimerMgr.h>

class Interpolator : public ITimer
{

private:

    float* m_fCurrentValue;
    float m_fInitialValue;
    float m_fDestValue;
    Ease m_easingFunction;
    float m_fProgress;
    unsigned int m_unDurationInMilliSeconds;

    void Progress();

public:

    void Start(float& fCurrentValue, float fInitialValue, float fDestValue, Ease easingFunction, unsigned int unDurationInMilliSeconds);
    void Stop(bool bReachDestValue = true);
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    const float& GetProgress();
    
};