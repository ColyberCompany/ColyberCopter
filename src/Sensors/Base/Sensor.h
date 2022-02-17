/**
 * @file Sensor.h
 * @author Jan Wielgus
 * @brief Base class for all sensor classes.
 * @date 2020-11-25
 * 
 */

#ifndef SENSOR_H
#define SENSOR_H

#include "Enums/SensorTypes.h"


class Sensor
{
    bool initResult_flag = false;
    const Enums::SensorTypes type;


public:
    Sensor(Enums::SensorTypes _type)
        : type(_type)
    {
    }

    Sensor(const Sensor&) = delete;
    Sensor& operator=(const Sensor&) = delete;
    virtual ~Sensor() {}

    /**
     * @brief Initialize the sensor.
     * @return true if sensor was initialized successfully, false otherwise.
     */
    bool initialize()
    {
        initResult_flag = initSensor();
        return initResult_flag;
    }

    /**
     * @brief Check if sensor was initialized with successful result.
     * @return true if sensor was initialized, false otherwise.
     */
    bool isInitialized() const
    {
        return initResult_flag;
    }

    /**
     * @brief Get type of the current sensor.
     */
    Enums::SensorTypes getType()
    {
        return type;
    }

    /**
     * @brief Check if sensor is can give good measurements at the moment.
     * @return true if sensor measurements are correct.
     */
    virtual bool isOperating() const
    {
        return initResult_flag; // by default
    }

    /**
     * @brief Name getter of this sensor.
     */
    virtual const char* getName() = 0;


private:
    /**
     * @brief Communicate with the sensor and initialze it.
     * @return whether initialization was successful or not.
     */
    virtual bool initSensor() = 0;
};


#endif

