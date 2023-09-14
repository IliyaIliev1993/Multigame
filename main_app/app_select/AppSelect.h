#pragma once

#include <main_app/IApp.h>
#include <main_app/texture/Texture.h>
#include <main_app/button/Button.h>
#include <main_app/applications/kids_fantasy/MainGame.h>

#include <map>


enum class EApps
{
    eKidsFantasy,
    eRoulette,
    eTotalAppsCount,
    eNoAppSelected
};

enum class EAppSelectStates
{
    eInactive,
    eReadyForSelection,
    eBusyInGame,
    eTotalAppSelectsStates
};

class AppSelect
{

private:

    /*boolean flags button hovered*/
    bool m_bIsKidsFantasyHovered = false;
    bool m_bIsRouletteHovered = false;

    /*Current active app*/
    EApps m_eCurrentApp = EApps::eNoAppSelected;

    /*Current AppSelect state*/
    EAppSelectStates m_eState = EAppSelectStates::eInactive;

    /*Container, holding all the registered IApp objects*/
    std::map<EApps, IApp*>m_mapAppClients;

    /*Texture main background*/
    std::shared_ptr<Texture>m_textureBackground;

    /*Kids Fantasy Button*/
    Button m_buttonKidsFantasy;

    /*Roulette Button*/
    Button m_buttonRoulette;

    /*Kids Fantasy object*/
    KidsFantasy m_KidsFantasy;


public:

    bool Init();
    bool Deinit();
    bool HandleEvent();
    const EAppSelectStates& GetState();
    void RegisterClient(EApps eApp, IApp* client);
    void UnregisterClient(EApps eApp, IApp* client);
    void OnDraw();
};
