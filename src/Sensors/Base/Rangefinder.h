/**
 * @file Rangefinder.h
 * @author Jan Wielgus
 * @brief Base class for all rangefinders.
 * @date 2021-08-12
 */

#ifndef __RANGEFINDER_H__
#define __RANGEFINDER_H__

#include "Sensor.h"


class Rangefinder : public Sensor
{
public:
    Rangefinder()
        : Sensor(Sensor::SensorTypes::RANGEFINDER)
    {
    }

    virtual ~Rangefinder() {}

    /**
     * @brief Current instance as rangefinder.
     */
    Rangefinder& rangefinder() {
        return *this;
    }

    virtual float getDistance_m() = 0;
};


#endif // __RANGEFINDER_H__
