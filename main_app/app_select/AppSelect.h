#pragma once

#include <main_app/IApp.h>
#include <main_app/texture/Texture.h>
#include <main_app/button/Button.h>

#include <vector>

class AppSelect
{

private:

    /*boolean flags button hovered*/
    bool m_bIsKidsFantasyHovered = false;
    bool m_bIsRouletteHovered = false;

    /*Container, holding all the registered IApp objects*/
    std::vector<IApp*>m_vecAppClients;

    /*Texture main background*/
    std::shared_ptr<Texture>m_textureBackground;

    /*Kids Fantasy Button*/
    Button m_buttonKidsFantasy;

    /*Roulette Button*/
    Button m_buttonRoulette;

public:

    bool Init();
    bool Deinit();
    bool HandleEvent();
    void RegisterClient(IApp* client);
    void UnregisterClient(IApp* client);
    void OnDraw();
};
