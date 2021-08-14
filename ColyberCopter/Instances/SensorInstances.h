/**
 * @file SensorInstances.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Instances of all sensor classes.
 * @date 2021-03-29
 */


#ifndef SENSORINSTANCES_H
#define SENSORINSTANCES_H

#include "Sensors/Base/Accelerometer.h"
#include "Sensors/Base/Gyroscope.h"
#include "Sensors/Base/Magnetometer.h"
#include "Sensors/Base/Barometer.h"
#include "Sensors/Base/GPS.h"
#include "Sensors/Base/Rangefinder.h"


namespace Instance
{
    extern Accelerometer& acc;
    extern Gyroscope& gyro;
    extern Magnetometer& magn;
    extern Barometer& baro;
    // extern other sensors...
}


#endif
