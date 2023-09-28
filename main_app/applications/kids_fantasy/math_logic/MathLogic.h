#pragma once
#include <array>
#include <main_app/applications/kids_fantasy/GameDefinitions.h>

typedef std::array<std::array<GameDefs::EGameFigure, GameDefs::eTotalFigurePositionsPerReel>, GameDefs::eTotalReelCount> Matrix2DResults;

class MathLogic
{

private:

    MathLogic();
    ~MathLogic();

    /*2D matrix 5x5 holding game results*/
    Matrix2DResults m_arrResults;

public:


    static MathLogic& GetInstance()
    {
        static MathLogic mathLogic;
        return mathLogic;
    }

    /** Delete copyt-constructor, move-constructor and assignment operators */
    MathLogic(MathLogic const&) = delete;
    void operator = (MathLogic const&) = delete;
    MathLogic(MathLogic &&) = delete;
    void operator = (MathLogic &&) = delete;

    bool Init();
    bool Deinit();

    /*Method that generates results in the current game*/
    void GenerateResults();

    /*Returns m_arrResults matrix, DO NOT FORGET TO CALL GenerateResults() !*/
    const Matrix2DResults& GetResults();

    /*Returns a random number in the interval (0, 10]*/
    long GenerateRandomNuber(long nLowerBoundOpenInterval, long nUpperBoundClosedInterval);

};