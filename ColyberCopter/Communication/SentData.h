/**
 * @file SentData.h
 * @author Jan Wielgus
 * @brief Structures with all variables that are sent.
 * @date 2020-11-05
 * 
 */

#ifndef SENTDATA_H
#define SENTDATA_H

#include <ByteTypes.h>


struct ForRemote
{
    int8Byte pitchAngle_deg;
    int8Byte rollAngle_deg;
    int16Byte heading_deg;
    int16Byte altitude_cm;
    int32Byte longitude; // TODO: add unit
    int32Byte latitude;

    uint8Byte droneConnectionStability;
};


#endif

