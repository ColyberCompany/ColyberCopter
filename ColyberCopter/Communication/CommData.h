/**
 * @file CommData.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief All communication variables.
 * @date 2021-03-28
 * 
 */

#ifndef COMMDATA_H
#define COMMDATA_H

#include <ByteTypes.h>


struct CommData
{
    struct {
        int8Byte pitchAngle_deg;
        int8Byte rollAngle_deg;
        int16Byte heading_deg;
        int16Byte altitude_cm;
        int32Byte longitude; // TODO: add unit (same in drone code)
        int32Byte latitude; // TODO: add unit (same in drone code)
        uint8Byte connectionStability;
    } drone;

    struct {
        struct {
            uint16Byte throttle;
            int16Byte yaw;
            int16Byte pitch;
            int16Byte roll;
        } stick;

        // TODO: consider adding pilot coordinates (polar or rectangular)
    } pilot;

    struct {
        uint8Byte tunedController_ID;
        floatByte kP;
        floatByte kI;
        floatByte kD;
        floatByte iMax;
    } pidTuning;


    uint8Byte flightMode;
    //uint8Byte signalLostScenario; // read todo below (probably in a drone code)
};

extern CommData commData;


#endif



// TODO: think about something like config packet, where will id of value to change, and in receive event proper setting will be changed based on this id.
// this will enable to remove flight mode, signalLostScenario and other simmilar variables.
// They won't have to be sent over and over again but only when this particular value has changed and make reaction only when needed
// (for example drone don't have to check each time if flight mode has changed).
// Make also something like confirmation packet.
// It would be good if this packets will be inside the library.
// Maybe make two types of config packets: one with config id and float value and second with config id and two float values.
