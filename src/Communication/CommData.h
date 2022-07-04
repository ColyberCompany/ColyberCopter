/**
 * @file CommData.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief All communication variables.
 * @date 2021-03-28
 */

#ifndef COMMDATA_H
#define COMMDATA_H

#include <cstdint>


struct CommData
{
    struct {
        int16_t anglePitch;     // centi deg (deg*100)
        int16_t angleRoll;      // centi deg (deg*100)
        int16_t heading;        // centi deg (deg*100)
        int16_t altitude;       // cm
        float longitude;        // deg
        float latitude;         // deg
    } droneMeasurements;

    // struct {
    //     int8_t accX;
    //     int8_t accY;
    //     int8_t accZ;
    //     int8_t gyroX;
    //     int8_t gyroY;
    //     int8_t gyroZ;
    //     int8_t magnX;
    //     int8_t magnY;
    //     int8_t magnZ;
    //     uint16_t pressure;          // daPa (deca Pascal) (hPa/10)
    //     uint16_t btmRangefinder;    // mm
    //     int8_t temperature;         // degC
    // } droneReadings;

    struct {
        uint8_t connectionStability;    // 0:100
    } droneState;

    struct {
        int16_t throttle;   // 0:1000
        int16_t yaw;        // -500:500
        int16_t pitch;      // -500:500
        int16_t roll;       // -500:500
    } steering;
    
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

    // uint8_t signalLostScenario; // read todo below (probably in a drone code)
};

extern CommData commData;


#endif



// TODO: think about something like config packet, where will id of value to change, and in receive event proper setting will be changed based on this id.
// this will enable to remove flight mode, signalLostScenario and other simmilar variables.
// They won't have to be sent over and over again but only when this particular value has changed and make reaction only when needed
// (for example drone don't have to check each time if flight mode has changed).
// Make also something like confirmation packet.
// It would be good if this packets will be inside the library.
