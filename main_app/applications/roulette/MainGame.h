#pragma once

#include <string>

#include <main_app/applications/IApp.h>
#include <main_app/applications/roulette/table_area/TableArea.h>
#include <main_app/applications/roulette/wheel_area/WheelArea.h>
#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>

class Roulette : public IApp, public ITimer
{

private:
    std::string m_strAppName = "Roulette";

    /*Texture main background*/
    std::shared_ptr<Texture> m_textureBackground;

    /*Wheel Area Object*/
    WheelArea m_wheelArea;

    /*Table Area Objet*/
    TableArea m_tableArea;
    

public:
    Roulette();

    bool Init() override;
    bool Deinit() override;
    bool HandleEvent() override;
    const std::string &GetAppName() override;
    void OnEnter() override;
    void OnExit() override;
    void OnDraw() override;
    void OnTick(unsigned int unID, unsigned int unTimes) final;
};
