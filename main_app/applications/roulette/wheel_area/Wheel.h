#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/interpolator/Interpolator.h>

class Wheel : public ITimer
{
private:

    /*Degrees Wheel*/
    float m_fDegreesWheel = 0.0f;

    /*Speed Wheel*/
    float m_fSpeedWheel = 0.0f;

    /*Check in which sector we are*/
    unsigned int m_unCounterSector = 0;

    /*Texture Wheel Table*/
    std::shared_ptr<Texture> m_textureWheelTable;

    /*Texture Wheel*/
    std::shared_ptr<Texture> m_textureWheel;

    /*Interpolator acceleration*/
    Interpolator m_interpolatorAcceleration;

    /*Method that check if angle > 360*/
    void NormalizeAngle();

public:

    bool Init();
    bool Deinit();
    void Draw();
    void StartSlowRotation();
    void StopSlowRotation();
    void StartFastRotation();
    void DecrementToSlowRotation();
    void OnTick(unsigned int unID, unsigned int unTimes) final;
    const float& GetSpeed();
    const float& GetDegrees();
};