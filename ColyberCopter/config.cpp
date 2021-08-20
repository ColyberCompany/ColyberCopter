/**
 * @file config.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Instances of default config values.
 * @date 2021-03-31
 * 
 */

#include "config.h"


namespace Config
{
    const uint16_t MainFrequency_Hz = 250;
    const uint16_t MainInterval_us = 1000000 / MainFrequency_Hz;
    const float MainInterval_s = 1.f / MainFrequency_Hz; // delta time between next main loop executions

    const Enums::BaudRateTypes RmtCtrlSerialBaudRate = Enums::BaudRateTypes::BAUD_115200;

    const uint16_t RmtCtrlReceivingFrequency_Hz = 220;

    const uint8_t MaxTaskerTasks = 25;

    const float TiltExceedingAngleThreshold = 67;

    const float AccLPFCutOffFreq = 10.f;
    //const float GyroLPFCutOffFreq = 10.f;

    const uint16_t ThrottleStickCenter = 500;

    const float LevelingPID_kP = 2.85f;
    const float LevelingPID_kI = 0.f;
    const float LevelingPID_kD = 0.67f;
    const uint16_t LevelingPID_IMax = 75;

    const float HeadHoldPID_kP = 2.24f;
    const float HeadHoldPID_kI = 1.11f;
    const float HeadHoldPID_kD = 0.97f;
    const uint16_t HeadHoldPID_IMax = 85;

    const float AltHoldPID_kP = 0.5f;
    const float AltHoldPID_kI = 0.f;
    const float AltHoldPID_kD = 0.5f;
    const uint16_t AltHoldPID_IMax = 0;

    const Common::vector3Int16 AccOffset = {67, -5, -14};
    const Common::vector3Int16 GyroOffset = {-142, 124, 5};
    const Common::vector3Int16 CompassOffset = {-38, -89, -151};
}
