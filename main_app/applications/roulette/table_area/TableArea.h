#pragma once

#include <main_app/applications/roulette/GameDefinitions.h>
#include <main_app/texture/Texture.h>
#include <main_app/button/Button.h>

class TableArea
{
private:

    /*Texture Table Bets*/
    std::shared_ptr<Texture> m_textureTableBets;

    /*Container holding textures buttons of bet chips*/
    std::array<Button, GameDefs::eTotalCountChips>m_arrBetChips;

public:
    bool Init();
    bool Deinit();
    bool HandleEvent();
    void Draw();
};