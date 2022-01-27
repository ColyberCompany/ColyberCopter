/**
 * @file TemperatureSensor.h
 * @author Jan Wielgus
 * @brief Base class for all temperature sensors.
 * @date 2021-08-18
 */

#ifndef __TEMPERATURESENSOR_H__
#define __TEMPERATURESENSOR_H__

#include "Sensor.h"


class TemperatureSensor : public Sensor
{
public:
    TemperatureSensor()
        : Sensor(Enums::SensorTypes::TEMPERATURE_SENSOR)
    {
    }

    virtual ~TemperatureSensor() {}

    virtual float getTemperature_degC() = 0;

    float getTemperature_K() {
        return getTemperature_degC() * 273.15f;
    }
};


#endif // __TEMPERATURESENSOR_H__