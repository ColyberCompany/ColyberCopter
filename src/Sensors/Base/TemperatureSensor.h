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
        : Sensor(Sensor::SensorTypes::TEMPERATURE_SENSOR)
    {
    }

    virtual ~TemperatureSensor() {}

    /**
     * @brief Current instance as temperature sensor.
     */
    TemperatureSensor& temperatureSensor() {
        return *this;
    }

    virtual float getTemperature_degC() = 0;

    float getTemperature_K() {
        return getTemperature_degC() * 273.15f;
    }
};


#endif // __TEMPERATURESENSOR_H__