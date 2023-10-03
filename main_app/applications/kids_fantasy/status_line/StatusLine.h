#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/font/Font.h>
#include <main_app/timer/TimerMgr.h>

enum EStatusLineScenarios
{
    eInsertCredit,
    ePressStartToRunNewGame,
    ePlayAtMaxBet,
    eWinTheMaxAmout,
    eGoodLuck,
    eTotalScenarioCount
};

class StatusLine : public ITimer
{

private:

    /*Main alpha value key between scenarios*/
    float m_fAlphaScenario = 1.0f;

    /*StatusLine current scenario*/
    EStatusLineScenarios m_eCurrentScenario = eInsertCredit;

    /*Font StatusLine*/
    std::shared_ptr<Font> m_fontStatusLine;

    /*Method that changed the StatusLine scenario*/
    void NextScenario();

public:

    bool Init();
    bool Deinit(); 
    void Draw();
    void StartScenario();
    void StopScenario();
    void NeedToShowGoodLuck();
    void OnTick(unsigned int unID, unsigned int unTimes) final;

};