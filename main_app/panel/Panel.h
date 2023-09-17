#pragma once

#include <main_app/texture/Texture.h>
#include <main_app/button/Button.h>

class Panel
{

private:

    /*Textures Home Button pressed, released*/
    std::shared_ptr<Texture>m_textureHomeButton;
    std::shared_ptr<Texture>m_textureHomeButtonPressed;

    /*Home Button*/
    Button m_homeButton;

public:

    bool Init();
    bool Deinit();
    bool HandleEvent();
    void OnDraw();
};