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
    /*Clear container with wins*/
    m_vectorWins.clear();

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

    /*Check for Lines win*/
    CheckForWins();

    /*Here is just a print logic of the lines*/
    if (!m_vectorWins.empty())
    {
        LOG_WARN("MathLogic - Win Element BEGIN ");
        for (const auto &element : m_vectorWins)
        {
            std::cout << "Line -> " << element.eLine + 1 << " Game Figure -> " << element.eGameFigure + 1 << " Figure Count -> " << element.unFigureCount << std::endl;
        }
        LOG_WARN("MathLogic - Win Element END ");
    }
}

void MathLogic::PushWinElementInContainer(const GameDefs::ELines eLine, const GameDefs::EGameFigure eGameFigure, const unsigned int unFigureCount)
{
    m_vectorWins.emplace_back(WinElement{eLine, eGameFigure, unFigureCount});
}

void MathLogic::CheckForWins()
{
    /*Check for Lines*/
    for (unsigned int currentLine = GameDefs::eLine1; currentLine < GameDefs::eTotalLinesCount; ++currentLine)
    {
        const auto &arrLineFigures = GameDefs::g_arrLines.at(currentLine);
        unsigned int unWinFiguresCount = 1;

        for (unsigned int reel = GameDefs::eFirstReel; reel < GameDefs::eTotalReelCount - 1; ++reel)
        {
            unsigned int unCurrentReel = reel;
            unsigned int unNextReel = reel + 1;
            unsigned int unCurrentFigurePosition = arrLineFigures.at(unCurrentReel);
            unsigned int unNexFigurePosition = arrLineFigures.at(unNextReel);

            GameDefs::EGameFigure eCurrentFigure = m_arrResults[unCurrentFigurePosition][unCurrentReel];
            GameDefs::EGameFigure eNextReelFigure = m_arrResults[unNexFigurePosition][unNextReel];

            if (eCurrentFigure == eNextReelFigure)
            {
                ++unWinFiguresCount;

                if (unWinFiguresCount == GameDefs::eTotalReelCount)
                {
                    PushWinElementInContainer((GameDefs::ELines)currentLine, eCurrentFigure, unWinFiguresCount);
                }
            }
            else
            {
                if (unWinFiguresCount >= GameDefs::g_unMinFiguresNeededToFormWin)
                {
                    PushWinElementInContainer((GameDefs::ELines)currentLine, eCurrentFigure, unWinFiguresCount);
                }

                break;
            }
        }
    }
}

const Matrix2DResults &MathLogic::GetResults()
{
    return m_arrResults;
}