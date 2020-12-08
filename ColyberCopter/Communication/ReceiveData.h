/**
 * @file ReceiveData.h
 * @author Jan Wielgus
 * @brief Structures for all received data.
 * @date 2020-11-05
 * 
 */

#ifndef RECEIVEDATA_H
#define RECEIVEDATA_H

#include <ByteTypes.h>


/**
 * @brief Data from remote contrller.
 */
struct DataFromRemoteControl
{
    uint16Byte throttle;
    int16Byte yaw;
    int16Byte pitch;
    int16Byte roll;

    uint16Byte pilotDistance_dm;
	uint16Byte pilotDirection;
    //uint8Byte flightMode; // read todo below
    //uint8Byte signalLostScenario; // read todo below

    uint8Byte tunedPID_ID;
    floatByte pidP;
    floatByte pidI;
    floatByte pidD;
    floatByte pidIMax;



    // TODO: think about something like config packet, where will id of value to change, and in receive event proper setting will be changed based on this id.
    // this will enable to remove flight mode, signalLostScenario and other simmilar variables.
    // They won't have to be sent over and over again but only when this particular value has changed and make reaction only when needed
    // (for example drone don't have to check each time if flight mode has changed).
    // Make also something like confirmation packet.
    // It would be good if this packets will be inside the library.
    // Maybe make two types of config packets: one with config id and float value and second with config id and two float values.
};


// Other received data ...


#endif

