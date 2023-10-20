#pragma once

#include <array>

namespace GameDefs
{
    constexpr float g_fWidthBallRoulette = 26.0f;
    constexpr float g_fHeightBallRoulette = 26.0f;

    constexpr float g_fAnglePerSector = 9.73f;

    enum class EColor
    {
        eRed,
        eBlack,
        eIsZero
    };

    enum class EEvenOdd
    {
        eEven,
        eOdd,
        eIsZero
    };

    enum class ETwelfth
    {
        eFirstTwelfth,
        eSecondTwelfth,
        eThirdTwelfth,
        eIsZero
    };

    enum class EByThree
    {
        eIsOneByThree,
        eIsTwoByThree,
        eIsThreeByThree,
        eIsZero
    };

    enum class EHalfTable
    {
        e1to18,
        e19to36,
        eIsZero
    };
    
    enum EChips
    {
        eChip_1,
        eChip_5,
        eChip_10,
        eChip_25,
        eChip_100,
        eChip_500,
        eTotalCountChips
    };

    enum EWheelSectors
    {
        eSector32,
        eSector15,
        eSector19,
        eSector4,
        eSector21,
        eSector2,
        eSector25,
        eSector17,
        eSector34,
        eSector6,
        eSector27,
        eSector13,
        eSector36,
        eSector11,
        eSector30,
        eSector8,
        eSector23,
        eSector10,
        eSector5,
        eSector24,
        eSector16,
        eSector33,
        eSector1,
        eSector20,
        eSector14,
        eSector31,
        eSector9,
        eSector22,
        eSector18,
        eSector29,
        eSector7,
        eSector28,
        eSector12,
        eSector35,
        eSector3,
        eSector26,
        eSector0,
        eTotalWheelSectorsCount
    };

    const std::array<unsigned int, eTotalWheelSectorsCount> g_arrSectorNumbers = 
    {
      32,
      15,
      19,
      4,
      21,
      2,
      25,
      17,
      34,
      6,
      27,
      13,
      36,
      11,
      30,
      8,
      23,
      10,
      5,
      24,
      16,
      33,
      1,
      20,
      14,
      31,
      9,
      22,
      18,
      29,
      7,
      28,
      12,
      35,
      3,
      26,
      0
    };
}