#include "MathLogic.h"

#include <cstdlib>
#include <iostream>
#include <debug/Logger.h>

MathLogic::MathLogic()
{
}

MathLogic::~MathLogic()
{
}

bool MathLogic::Init()
{

    LOG_INFO("MathLogic - Initialized ...");
    return true;
}

bool MathLogic::Deinit()
{
    LOG_INFO("MathLogic - Deinitialized ...");
    return true;
}

long MathLogic::GenerateRandomNuber(long nLowerBound, long nUpperBound)
{
    long nNumberToReturn = rand() % nUpperBound + nLowerBound;

    // LOG_INFO("MathLogic - Generated Random Number - \"{0}\"", nNumberToReturn);

    return nNumberToReturn;
}

void MathLogic::GenerateResults()
{
    /*Generate random numbers with rand()*/
    for (unsigned int figure = GameDefs::eFirstPositionNONVisible; figure < GameDefs::eTotalFigurePositionsPerReel; ++figure)
    {
        for (unsigned int reel = GameDefs::eFirstReel; reel < GameDefs::eTotalReelCount; ++reel)
        {
            m_arrResults[figure][reel] = (GameDefs::EGameFigure)GenerateRandomNuber(GameDefs::eGameFigureOne, GameDefs::eTotalGameFiguresCount);
        }
    }

    /*Here is just a print logic*/
    LOG_WARN("MathLogic - Generated Results BEGIN ");
    for (unsigned int figure = GameDefs::eFirstPositionNONVisible; figure < GameDefs::eTotalFigurePositionsPerReel; ++figure)
    {
        for (unsigned int reel = GameDefs::eFirstReel; reel < GameDefs::eTotalReelCount; ++reel)
        {
            std::cout << m_arrResults[figure][reel] + 1 << "   ";
        }

        std::cout << std::endl;
    }
    LOG_WARN("MathLogic - Generated Results END ");
}

const Matrix2DResults &MathLogic::GetResults()
{
    return m_arrResults;
}