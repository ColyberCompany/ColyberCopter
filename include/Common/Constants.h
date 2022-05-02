/**
 * @file Constants.h
 * @author Jan Wielgus
 * @brief Shared constants in code.
 * This file should not be used for configuration.
 * @date 2020-11-04
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>


namespace Common
{
    namespace Consts
    {
        inline constexpr float RoundAngle = 360.f;
        inline constexpr float StraightAngle = 180.f;
        inline constexpr float DegToRad = 0.0174533f;
        inline constexpr float RadToDeg = 57.29577f;

        inline constexpr uint16_t ThrottleStickCenter = 500;

        inline constexpr float GravitationalAcceleration = 9.81f;

        inline const char* const OKText = "OK";
    }
} 


#endif
