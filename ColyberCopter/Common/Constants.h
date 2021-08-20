/**
 * @file Constants.h
 * @author Jan Wielgus
 * @brief Shared constants in code.
 * This file should not be used for configuration.
 * @date 2020-11-04
 * 
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace Common
{
    namespace Consts
    {
        inline constexpr float RoundAngle = 360.f;
        inline constexpr float StraightAngle = 180.f;

        inline constexpr uint16_t ThrottleStickCenter = 500;

        inline const char* const OKText = "OK";
    }
} 


#endif
