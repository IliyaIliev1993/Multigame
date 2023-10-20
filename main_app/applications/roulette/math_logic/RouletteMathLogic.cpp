#include "RouletteMathLogic.h"

#include <cstdlib>
#include <iostream>
#include <main_app/panel/Panel.h>
#include <debug/Logger.h>

RouletteMathLogic::RouletteMathLogic()
{
}

RouletteMathLogic::~RouletteMathLogic()
{
}

bool RouletteMathLogic::Init()
{
    FillContainerWinSectors();

    LOG_INFO("MathLogic - Roulette - Initialized ...");
    return true;
}

bool RouletteMathLogic::Deinit()
{
    ResetValuesToWinSector();
    LOG_WARN("MathLogic - Roulette - Deinitialized ...");
    return true;
}

void RouletteMathLogic::FillContainerWinSectors()
{
    for(unsigned int i = 0; i < GameDefs::EWheelSectors::eTotalWheelSectorsCount; ++i)
    {
        AssingValuesToWinSector(i);
        m_arrWinSectors.at(i) = m_winSector;
    }

    ResetValuesToWinSector();
}

void RouletteMathLogic::GenerateResults()
{
    LOG_WARN("MathLogic - Roulette - Generated Results BEGIN ");

    /*Generate random number in range (0, 37]*/
    const unsigned int unGeneratedNumber = GenerateRandomNumber(GameDefs::EWheelSectors::eSector32, GameDefs::EWheelSectors::eTotalWheelSectorsCount);

    /*Assing values*/
    AssingValuesToWinSector(unGeneratedNumber);

    /*Just print logic*/
    std::cout << "Winning Sector - " << m_winSector.eWinningSector << std::endl;
    std::cout << "Winning Sector NUMBER - " << m_winSector.unWinningSectorNumber << std::endl;

    if(m_winSector.unWinningSectorNumber == 0)
    {
        std::cout << "IS ZERO !!!" << std::endl;
    }

    /*Color*/
    if (m_winSector.eColor == GameDefs::EColor::eRed)
    {
        std::cout << "Winning Sector COLOR - "
                  << "Red" << std::endl;
    }
    else if (m_winSector.eColor == GameDefs::EColor::eBlack)
    {
        std::cout << "Winning Sector COLOR - "
                  << "Black" << std::endl;
    }

    /*Even - Odd*/
    if(m_winSector.eEvenOdd == GameDefs::EEvenOdd::eEven)
    {
        std::cout << "Winning Sector EVEN/ODD - "
                  << "Even" << std::endl;
    }
    else if(m_winSector.eEvenOdd == GameDefs::EEvenOdd::eOdd)
    {
        std::cout << "Winning Sector EVEN/ODD - "
                  << "Odd" << std::endl;
    }

    /*Twelfth*/
    if(m_winSector.eTwelfth == GameDefs::ETwelfth::eFirstTwelfth)
    {
        std::cout << "Winning Sector TWELFTH - "
                  << "1st 12" << std::endl;
    }
    else if(m_winSector.eTwelfth == GameDefs::ETwelfth::eSecondTwelfth)
    {
        std::cout << "Winning Sector TWELFTH - "
                  << "2nd 12" << std::endl;
    }
    else if(m_winSector.eTwelfth == GameDefs::ETwelfth::eThirdTwelfth)
    {
        std::cout << "Winning Sector TWELFTH - "
                  << "3rd 12" << std::endl;
    }

    /*By Three*/
    if(m_winSector.eByThree == GameDefs::EByThree::eIsOneByThree)
    {
        std::cout << "Winning Sector BY THREE - "
                  << "1 by 3" << std::endl;
    }
    else if(m_winSector.eByThree == GameDefs::EByThree::eIsTwoByThree)
    {
        std::cout << "Winning Sector BY THREE - "
                  << "2 by 3" << std::endl;
    }
    else if(m_winSector.eByThree == GameDefs::EByThree::eIsThreeByThree)
    {
        std::cout << "Winning Sector BY THREE - "
                  << "3 by 3" << std::endl;
    }

    /*Half Table*/
    if(m_winSector.eHalfTable == GameDefs::EHalfTable::e1to18)
    {
        std::cout << "Winning Sector HALF TABLE - "
                  << "1 to 18" << std::endl;
    }
    else if(m_winSector.eHalfTable == GameDefs::EHalfTable::e19to36)
    {
        std::cout << "Winning Sector HALF TABLE - "
                  << "19 to 36" << std::endl;
    }
    /*****************/

    LOG_WARN("MathLogic - Roulette - Generated Results END ");
}

void RouletteMathLogic::AssingValuesToWinSector(const unsigned int &unGeneratedNumber)
{
    /*Assing the generated random number to the winning sector*/
    m_winSector.eWinningSector = (GameDefs::EWheelSectors)unGeneratedNumber;

    /*Assing the winnin sector value*/
    m_winSector.unWinningSectorNumber = GameDefs::g_arrSectorNumbers.at(unGeneratedNumber);

    switch (m_winSector.eWinningSector)
    {

    case GameDefs::EWheelSectors::eSector0:
    {
        m_winSector.eColor = GameDefs::EColor::eIsZero;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eIsZero;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eIsZero;
        m_winSector.eByThree = GameDefs::EByThree::eIsZero;
        m_winSector.eHalfTable = GameDefs::EHalfTable::eIsZero;
    }
    break;

    case GameDefs::EWheelSectors::eSector1:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector2:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector3:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector4:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector5:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector6:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector7:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector8:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector9:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector10:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector11:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector12:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eFirstTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector13:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector14:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector15:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector16:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector17:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector18:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e1to18;
    }
    break;

    case GameDefs::EWheelSectors::eSector19:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector20:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector21:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector22:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector23:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector24:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eSecondTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector25:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector26:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector27:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector28:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector29:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector30:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector31:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector32:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector33:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector34:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsOneByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector35:
    {
        m_winSector.eColor = GameDefs::EColor::eBlack;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eOdd;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsTwoByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    case GameDefs::EWheelSectors::eSector36:
    {
        m_winSector.eColor = GameDefs::EColor::eRed;
        m_winSector.eEvenOdd = GameDefs::EEvenOdd::eEven;
        m_winSector.eTwelfth = GameDefs::ETwelfth::eThirdTwelfth;
        m_winSector.eByThree = GameDefs::EByThree::eIsThreeByThree;
        m_winSector.eHalfTable = GameDefs::EHalfTable::e19to36;
    }
    break;

    default:
        LOG_WARN("MathLogic - Roulette - INVALID Sector ");
        ResetValuesToWinSector();
        break;
    }
}

void RouletteMathLogic::ResetValuesToWinSector()
{
    m_winSector.eWinningSector = GameDefs::EWheelSectors::eSector0;
    m_winSector.unWinningSectorNumber = 36;
    m_winSector.eColor = GameDefs::EColor::eIsZero;
    m_winSector.eEvenOdd = GameDefs::EEvenOdd::eIsZero;
    m_winSector.eTwelfth = GameDefs::ETwelfth::eIsZero;
    m_winSector.eByThree = GameDefs::EByThree::eIsZero;
    m_winSector.eHalfTable = GameDefs::EHalfTable::eIsZero;

    LOG_WARN("MathLogic - Roulette - RESET Win Sector ");
}

const GameDefs::EWheelSectors &RouletteMathLogic::GetWinningSector()
{
    return m_winSector.eWinningSector;
}

const unsigned int &RouletteMathLogic::GetWinningSectorNumber()
{
    return m_winSector.unWinningSectorNumber;
}

const GameDefs::EColor &RouletteMathLogic::GetWinningSectorColor()
{
    return m_winSector.eColor;
}

const std::array<WinSector, GameDefs::eTotalWheelSectorsCount>& RouletteMathLogic::GetContainerWinSectors()
{
    return m_arrWinSectors;
}

long RouletteMathLogic::GenerateRandomNumber(long nLowerBound, long nUpperBound)
{
    unsigned int unSeed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(unSeed);
    long nNumberToReturn = rand() % nUpperBound + nLowerBound;

    // LOG_INFO("MathLogic - Roulette - Generated Random Number - \"{0}\"", nNumberToReturn);

    return nNumberToReturn;
}