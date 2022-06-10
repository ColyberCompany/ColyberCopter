/**
 * @file CommData.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief All communication variables.
 * @date 2021-03-28
 * 
 */

#ifndef COMMDATA_H
#define COMMDATA_H

#include <cstdint>


struct CommData
{
    struct {
        int8_t pitchAngle_deg;
        int8_t rollAngle_deg;
        int16_t heading_deg;
        int16_t altitude_cm;
        int32_t longitude; // TODO: add unit (same in drone code)
        int32_t latitude; // TODO: add unit (same in drone code)
        uint8_t connectionStability;
    } droneMeasurementsAndState;

    struct {
        uint16_t throttle;
        int16_t yaw;
        int16_t pitch;
        int16_t roll;
    } steering;
    // TODO: consider adding pilot coordinates (polar or rectangular)
    
    struct {
        uint8_t tunedController_ID;
        float kP;
        float kI;
        float kD;
        float iMax;
    } pidTuning;

    struct {
        uint8_t flightMode;
    } flightModeChange;
    //uint8_t signalLostScenario; // read todo below (probably in a drone code)
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
