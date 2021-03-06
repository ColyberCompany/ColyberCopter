/**
 * @file NoSensor.h
 * @author Jan Wielgus
 * @brief Instance put instead of the particular sensor instance
 * if this sensor is not available.
 * @date 2020-12-01
 * 
 */

#ifndef NOSENSOR_H
#define NOSENSOR_H

#include "Sensor.h"
#include "SensorsMediator.h"


class NoSensor: public Sensor
{
public:
    NoSensor(SensorsMediator& sensorsMediator)
        : Sensor(Enums::SensorTypes::NO_SENSOR, sensorsMediator)
    {}

    bool initialize() override
    {
        return false;
    }

    bool isGood() const override
    {
        return false;
    }

    uint16_t startBackgroundCalibration(uint16_t) override
    {
        return 0;
    }

    FloatAxisVector getOffset() const
    {
        return FloatAxisVector(0);
    }

    void setOffset(FloatAxisVector) override
    {
    }

    const char* getName() override
    {
        return "no sensor";
    }
};


#endif

