/**
 * @file config.h
 * @author Jan Wielgus
 * @brief This is the configuraiton file.
 * @date 2020-11-09
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "Enums/BaudRateTypes.h"
#include <cstdint>
#include <cstddef>


namespace Config
{
    inline constexpr float MainFrequency_Hz = 250.f;
    inline constexpr uint32_t MainInterval_us = 4000; // = 1000000 / MainFrequency_Hz;
    inline constexpr float MainInterval_s = 0.004f; // = 1.f / MainFrequency_Hz; // delta time between next main loop executions

    inline constexpr Enums::BaudRateTypes RmtCtrlSerialBaudRate = Enums::BaudRateTypes::BAUD_115200;
    inline constexpr size_t RmtCtrlMaxComBufferSize = 40;
    inline constexpr uint16_t RmtCtrlReceivingFrequency_Hz = 20;

    inline constexpr uint8_t MaxTaskerTasks = 25;

    inline constexpr float StabilizeMaxTiltAngle_deg = 50; // setpoint angle for maximum stick position (pitch, roll) (maximum tilt angle in stabilize flight mode)

    inline constexpr float LevelingPID_kP = 2.85f;
    inline constexpr float LevelingPID_kI = 1.4f;
    inline constexpr float LevelingPID_kD = 0.67f;
    inline constexpr uint16_t LevelingPID_IMax = 90;

    inline constexpr float HeadHoldPID_kP = 2.24f;
    inline constexpr float HeadHoldPID_kI = 1.11f;
    inline constexpr float HeadHoldPID_kD = 0.97f;
    inline constexpr uint16_t HeadHoldPID_IMax = 85;

    inline constexpr float AltHoldPID_kP = 0.4f;
    inline constexpr float AltHoldPID_kI = 0.2f;
    inline constexpr float AltHoldPID_kD = 0.5f;
    inline constexpr uint16_t AltHoldPID_IMax = 100;

    // inline constexpr Common::vector3Int16 AccOffset = {67, -5, -14};
    // inline constexpr Common::vector3Int16 GyroOffset = {-142, 124, 5};
    // inline constexpr Common::vector3Int16 CompassOffset = {-38, -89, -151};
    

    inline constexpr float MaxTiltCompThrMult = 1.5f;
}


#endif

