/**
 * @file ReceivedData.h
 * @author Jan Wielgus
 * @brief Structures for all received data.
 * @date 2020-11-05
 * 
 */

#ifndef RECEIVEDDATA_H
#define RECEIVEDDATA_H

#include <ByteTypes.h>


struct FromRemote
{
    uint16Byte throttle;
    int16Byte yaw;
    int16Byte pitch;
    int16Byte roll;

    uint16Byte pilotDistance_dm;
	uint16Byte pilotDirection;
    uint8Byte flightMode;
    uint8Byte signalLostScenario;

    uint8Byte tunedPID_ID;
    floatByte pidP;
    floatByte pidI;
    floatByte pidD;
    floatByte pidIMax;


    // TODO: think about something like config packet, where will be change ID and value, and in receive event proper setting will be changed.
    // this will enable to remove flight mode, signalLostScenario and other simmilar variables.
}


#endif

