/**
 * @file SendData.h
 * @author Jan Wielgus
 * @brief Structures with all variables that are sent.
 * @date 2020-11-05
 * 
 */

#ifndef SENDDATA_H
#define SENDDATA_H

#include <ByteTypes.h>


/**
 * @brief Data for remote contrller.
 */
struct DataForRmtCtrl
{
    int8Byte pitchAngle_deg;
    int8Byte rollAngle_deg;
    int16Byte heading_deg;
    int16Byte altitude_cm;
    int32Byte longitude; // TODO: add unit
    int32Byte latitude; // TODO: add unit

    uint8Byte droneConnectionStability;
};


#endif

