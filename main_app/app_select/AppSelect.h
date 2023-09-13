#pragma once

#include <main_app/IApp.h>
#include <main_app/texture/Texture.h>

#include <vector>

class AppSelect
{

private:

    /*Container, holding all the registered IApp objects*/
    std::vector<IApp*>m_vecAppClients;

    /*Texture main background*/
    std::shared_ptr<Texture>m_textureBackground;

    /*Kids Fantasy Button*/
    std::shared_ptr<Texture>m_textureKidsFantasyButton;

    /*Roulette Button*/
    std::shared_ptr<Texture>m_textureRouletteButton;

public:

    bool Init();
    bool Deinit();
    void RegisterClient(IApp* client);
    void UnregisterClient(IApp* client);
    void OnDraw();


};
