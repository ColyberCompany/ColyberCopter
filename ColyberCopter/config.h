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
#include "Common/Vector3.h"
#include <cstdint>
#include <cstddef>


namespace Config
{
    extern const float MainFrequency_Hz;
    extern const uint32_t MainInterval_us;
    extern const float MainInterval_s; // delta time between next main loop executions

    extern const Enums::BaudRateTypes RmtCtrlSerialBaudRate;

    inline constexpr size_t RmtCtrlMaxComBufferSize = 40;
    extern const uint16_t RmtCtrlReceivingFrequency_Hz;

    extern const uint8_t MaxTaskerTasks;

    extern const float TiltExceedingAngleThreshold;

    extern const float AccLPFCutOffFreq;
    extern const float GyroLPFCutOffFreq;

    extern const uint16_t ThrottleStickCenter;

    extern const float LevelingPID_kP;
    extern const float LevelingPID_kI;
    extern const float LevelingPID_kD;
    extern const uint16_t LevelingPID_IMax;

    extern const float HeadHoldPID_kP;
    extern const float HeadHoldPID_kI;
    extern const float HeadHoldPID_kD;
    extern const uint16_t HeadHoldPID_IMax;

    extern const float AltHoldPID_kP;
    extern const float AltHoldPID_kI;
    extern const float AltHoldPID_kD;
    extern const uint16_t AltHoldPID_IMax;

    extern const Common::vector3Int16 AccOffset;
    extern const Common::vector3Int16 GyroOffset;
    extern const Common::vector3Int16 CompassOffset;
}


#endif

