/**
 * @file config.h
 * @author Jan Wielgus
 * @brief This is the configuraiton file.
 * @date 2020-11-09
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H


namespace Config
{
    Stream& RmtCtrlSerial = Serial2;
    const size_t RmtCtrlMaxComBufferSize = 40;
    const size_t RmtCtrlMaxQueuedBuffers = 30;
    const uint16_t MainFrequency_Hz = 250;
    const uint16_t MainInterval_us = 1000000 / MainFrequency_Hz;
    const float MainInterval_s = 1.f / MainFrequency_Hz; // delta time between next main loop executions
}


#endif

