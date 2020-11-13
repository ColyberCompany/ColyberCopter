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
}


#endif

