/**
 * @file config.h
 * @author Jan Wielgus
 * @brief This is the configuraiton file.
 * @date 2020-11-09
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "Enums/BaudRateTypes.h"
#include <cstdint>
#include <cstddef>

#define CI constexpr inline

namespace Config
{
    CI float MainFrequency_Hz = 390.625f;
    CI uint32_t MainInterval_us = 2560; // = 1000000 / MainFrequency_Hz;
    CI float MainInterval_s = 0.00256f; // = 1.f / MainFrequency_Hz; // delta time between next main loop executions

    CI Enums::BaudRateTypes RmtCtrlSerialBaudRate = Enums::BaudRateTypes::BAUD_115200;
    CI size_t RmtCtrlMaxComBufferSize = 40;
    CI uint16_t RmtCtrlReceivingFrequency_Hz = 20;

    CI uint8_t MaxTaskerTasks = 25;

    CI float StabilizeMaxTiltAngle_deg = 50; // setpoint angle for maximum stick position (pitch, roll) (maximum tilt angle in stabilize flight mode)

    CI float LevelingPID_kP = 2.6f;
    CI float LevelingPID_kI = 0.37f;
    CI float LevelingPID_kD = 0.91f;
    CI uint16_t LevelingPID_IMax = 100;

    CI float HeadHoldPID_kP = 2.24f;
    CI float HeadHoldPID_kI = 1.11f;
    CI float HeadHoldPID_kD = 0.97f;
    CI uint16_t HeadHoldPID_IMax = 85;

    CI float AltHoldPID_kP = 0.4f;
    CI float AltHoldPID_kI = 0.2f;
    CI float AltHoldPID_kD = 0.5f;
    CI uint16_t AltHoldPID_IMax = 100;

    // CI Common::vector3Int16 AccOffset = {67, -5, -14};
    // CI Common::vector3Int16 GyroOffset = {-142, 124, 5};
    // CI Common::vector3Int16 CompassOffset = {-38, -89, -151};
    

    CI float MaxTiltCompThrMult = 1.5f;
}

#undef CI

#endif

