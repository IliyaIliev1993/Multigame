#pragma once

#include <vector>
#include <main_app/applications/roulette/GameDefinitions.h>

struct WinSector
{
    GameDefs::EWheelSectors eWinningSector = GameDefs::EWheelSectors::eSector0;
    unsigned int unWinningSectorNumber = 36;
    GameDefs::EColor eColor = GameDefs::EColor::eIsZero;
    GameDefs::EEvenOdd eEvenOdd = GameDefs::EEvenOdd::eIsZero;
    GameDefs::ETwelfth eTwelfth = GameDefs::ETwelfth::eIsZero;
    GameDefs::EByThree eByThree = GameDefs::EByThree::eIsZero;
    GameDefs::EHalfTable eHalfTable = GameDefs::EHalfTable::eIsZero;
};

class RouletteMathLogic
{

private:
    RouletteMathLogic();
    ~RouletteMathLogic();

    /*Container with all the winning sectors*/
    std::array<WinSector, GameDefs::eTotalWheelSectorsCount> m_arrWinSectors;

    /*Win Sector Object, generated in every new game*/
    WinSector m_winSector;

    /*Method called at Init*/
    void FillContainerWinSectors();

    /*Assing all values when number generated*/
    void AssingValuesToWinSector(const unsigned int& unGeneratedNumber);

    /*Reset all values to zero*/
    void ResetValuesToWinSector();

public:
    static RouletteMathLogic &GetInstance()
    {
        static RouletteMathLogic mathLogic;
        return mathLogic;
    }

    /** Delete copyt-constructor, move-constructor and assignment operators */
    RouletteMathLogic(RouletteMathLogic const &) = delete;
    void operator=(RouletteMathLogic const &) = delete;
    RouletteMathLogic(RouletteMathLogic &&) = delete;
    void operator=(RouletteMathLogic &&) = delete;

    bool Init();
    bool Deinit();

    /*Method that generates results in the current game*/
    void GenerateResults();

    /*Returns m_winSector.eWinningSector*/
    const GameDefs::EWheelSectors& GetWinningSector();

    /*Returns m_winSector.unWinningSectorNumber*/
    const unsigned int& GetWinningSectorNumber();

    /*Returns m_winSector.eColor*/
    const GameDefs::EColor& GetWinningSectorColor();
    
    /*Returns container with all winning sectors*/
    const std::array<WinSector, GameDefs::eTotalWheelSectorsCount>& GetContainerWinSectors();

    /*Returns a random number in the interval (0, 10]*/
    long GenerateRandomNumber(long nLowerBoundOpenInterval, long nUpperBoundClosedInterval);
};