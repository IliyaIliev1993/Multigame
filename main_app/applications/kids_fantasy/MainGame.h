#pragma once

#include <string>

#include <main_app/applications/IApp.h>
#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/applications/kids_fantasy/reels_area/ReelsArea.h>
#include <main_app/applications/kids_fantasy/status_line/StatusLine.h>

class KidsFantasy : public IApp, public ITimer
{

private:

    enum class EKidsFantasyStates
    {
        eInactive,
        eReadyForGame,
        eReeling,
        eAfterReelingStopped,
        eWinFromGame,
        eTotalStatesCount
    };

    std::string m_strAppName = "Kids Fantasy";

    /*KidsFantasy current state*/
    EKidsFantasyStates m_eState = EKidsFantasyStates::eInactive;

    /*Reels Area object*/
    ReelsArea m_reelsArea;

    /*StatusLine object*/
    StatusLine m_statusLine;

    /*Texture main background*/
    std::shared_ptr<Texture>m_textureBackground;

    /*After reeling stopped method, called when all reels stopped after game started*/
    void AfterReelingStopped();
    
    /*Game State Request*/
    void RequestState(EKidsFantasyStates eStateToRequest);
public:

    KidsFantasy();

    bool Init() override;
    bool Deinit() override;
    bool HandleEvent() override;
    const std::string& GetAppName() override;
    void OnEnter() override;
    void OnExit() override;
    void OnDraw() override;
    void OnTick(unsigned int unID, unsigned int unTimes) final;
};