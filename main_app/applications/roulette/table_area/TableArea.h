#pragma once

#include <main_app/applications/roulette/GameDefinitions.h>
#include <main_app/interpolator/Interpolator.h>
#include <main_app/texture/Texture.h>
#include <main_app/button/Button.h>

struct Chip
{
    bool bIsSelectedForBet = false;
    Interpolator m_interpolatorChipUp;
    Interpolator m_interpolatorChipDown;
    Button buttonChip;
};

struct Sector
{
    Button buttonSector;
};

class TableArea
{
private:
    /*True if any chip selected*/
    bool m_bIsAnyChipSelected = false;

    /*Texture Table Bets*/
    std::shared_ptr<Texture> m_textureTableBets;

    /*Texture Chips Table*/
    std::shared_ptr<Texture> m_textureChipsTable;

    /*Container holding textures buttons of bet chips*/
    std::array<Chip, GameDefs::eTotalCountChips> m_arrBetChips;

    /*Fade effect table bets when hovered*/
    Interpolator m_interpolatorFadeInTableBets;
    Interpolator m_interpolatorFadeOutTableBets;

    /*Button Bet Table, used just to use the Hover logic*/
    Button m_buttonTableBets;

    Sector m_sectorTest;

public:
    bool Init();
    bool Deinit();
    bool HandleEvent();
    void Draw();
};