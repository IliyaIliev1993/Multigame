#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/timer/TimerMgr.h>

class ReelsArea
{

private:

    /*Texture Reels Area*/
    std::shared_ptr<Texture>m_textureReelsArea;

public:

    bool Init();
    bool Deinit();
    bool HandleEvent();
    void Draw();

};