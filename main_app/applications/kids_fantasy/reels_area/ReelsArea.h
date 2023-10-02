#pragma once

#include <main_app/applications/kids_fantasy/GameDefinitions.h>
#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>
#include <main_app/applications/kids_fantasy/reels_area/reels/Reel.h>

class ReelsArea
{

private:
    /*Texture Reels Area*/
    std::shared_ptr<Texture> m_textureReelsArea;

    /*Texture Hearth*/
    std::shared_ptr<Texture> m_textureHearth;

    /*Container with reels*/
    std::array<Reel, GameDefs::eTotalReelCount> m_arrReels;

    /*Container with figure textures*/
    std::array<std::shared_ptr<Texture>, GameDefs::eTotalGameFiguresCount> m_arrFiguresTexture;

    /*Start new game method, when ENTER pressed will be executed*/
    void StartNewGame();

public:
    bool Init();
    bool Deinit();
    bool HandleEvent();
    void Draw();
};