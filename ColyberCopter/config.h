/**
 * @file config.h
 * @author Jan Wielgus
 * @brief This is the configuraiton file.
 * @date 2020-11-09
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

#ifdef ARDUINO
    #include <Arduino.h>
#endif

#include "Enums/BaudRateTypes.h"


namespace Config
{
    const uint16_t MainFrequency_Hz = 250;
    const uint16_t MainInterval_us = 1000000 / MainFrequency_Hz;
    const float MainInterval_s = 1.f / MainFrequency_Hz; // delta time between next main loop executions

    const Enums::BaudRateTypes RmtCtrlSerialBaudRate = Enums::BaudRateTypes::BAUD_115200;

    const size_t RmtCtrlMaxComBufferSize = 40;
    const size_t RmtCtrlMaxQueuedBuffers = 30;
    const uint16_t RmtCtrlReceivingFrequency_Hz = 220;

    const uint8_t MaxTaskerTasks = 25;

    const float TiltExceedingAngleThreshold = 60;

    const float AccLPFCutOffFreq = 5.f;
	const float GyroLPFCutOffFreq = 10.f;

    const uint16_t ThrottleStickCenter = 500;
}


#endif

