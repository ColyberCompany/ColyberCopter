/**
 * @file SensorInstances.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Instances of all sensor classes.
 * @date 2021-03-29
 * 
 */


#ifndef SENSORINSTANCES_H
#define SENSORINSTANCES_H

#include "../Sensors/Sensor.h"


namespace Instance
{
    extern Sensor& accel;
    extern Sensor& gyro;
    extern Sensor& magn;
    extern Sensor& baro;
    extern Sensor& gps;
    extern Sensor& btmRangefinder;
    // extern other sensors...
}


#endif
