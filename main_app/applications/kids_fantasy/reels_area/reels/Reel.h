#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/applications/kids_fantasy/GameDefinitions.h>

struct Figure
{
    float fXPos = 0.0f;
    float fYPos = 0.0f;
    GameDefs::EGameFigure eGameFigure = GameDefs::eGameFigureOne;
    GameDefs::EFigurePositionPerReel eFigurePosition = GameDefs::eFirstPositionNONVisible;
    std::shared_ptr<Texture> textureFigure = nullptr;
};

class Reel : public ITimer
{

private:

    /*ID current reel*/
    GameDefs::EReels m_eIDReel = GameDefs::EReels::eFirstReel;

    /*X Position reel*/
    float m_fXOrgPos = 0;

    /*Y Position reel*/
    float m_fYOrgPos = 0;

    /*Min Y Figure value while reeling*/
    float m_fYMinTresholdReelingFigure = 0;

    /*Max Y Figure value while reeling*/
    float m_fYMaxTresholdReelingFigure = 0;

    /*Array holding reel figures*/
    std::array<Figure, GameDefs::g_unTotalFiguresPerReel>m_arrReelFigures;

    /*Method called every tick of reeling timer*/
    void ProcessReeling();

public:

    bool Init(GameDefs::EReels eIDReel, float fXOrgPos, float fYOrgPos);
    void Draw();
    virtual void OnTick(unsigned int unID, unsigned int unTimes) final;

};