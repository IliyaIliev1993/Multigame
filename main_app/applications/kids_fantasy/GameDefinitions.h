#pragma once

namespace GameDefs
{
    enum EGameFigure
    {
        eGameFigureOne,
        eGameFigureTwo,
        eGameFigureThree,
        eGameFigureFour,
        eGameFigureFive,
        eGameFigureSix,
        eTotalGameFiguresCount
    };

    enum EReels
    {
        eFirstReel,
        eSecondReel,
        eThirdReel,
        eFourthReel,
        eFifthReel,
        eTotalReelCount
    };

    enum EFigurePositionPerReel
    {
        eFirstPositionNONVisible,
        eSecondPositionVisible,
        eThirdPositionVisible,
        eFourhtPositionVisible,
        eFifthPositionNONVisible,
        eTotalFigurePositionsPerReel
    };
    
    constexpr unsigned int g_unVisibleFiguresPerReel = 3;
    constexpr unsigned int g_unTotalFiguresPerReel = 5;

    constexpr float g_fWidthFigurePicture = 240.0f;
    constexpr float g_fHeightFigurePicture = 220.0f;
}