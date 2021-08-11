/**
 * @file Sensor.h
 * @author Jan Wielgus
 * @brief Base class for all sensor classes.
 * @date 2020-11-25
 * 
 */

#ifndef SENSOR_H
#define SENSOR_H

#include "../Common/FloatAxisVector.h"
#include "../Enums/SensorTypes.h"


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
     * @brief Check if sensor is currently updating new measurements in sensorsMediator.
     * @return true if sensor is running.
     */
    virtual bool isOperating() const
    {
        return initResult_flag; // by default
    }

    /**
     * @brief Name getter of this sensor.
     */
    virtual const char* getName() = 0;

    /**
     * @brief Get type of the current sensor.
     */
    Enums::SensorTypes getType()
    {
        return type;
    }

    /**
     * @brief After calling this method sensor will begin calibration during
     * it's normal execution and after that it will apply new offset values.
     * @param amtOfSamples Amount of samples that for example are averaged during calibration
     * (bigger amount -> longer calibration process and better results).
     * @return Amount of seconds that the calibration process will take.
     * You can call getOffset() method after that time and get new offset values.
     */
    virtual uint16_t startBackgroundCalibration(uint16_t amtOfSamples) // TODO: calibration process to rebuild (issue on github)
    {
        // Don't need to calibrate by default
        return 0;
    }

    /**
     * @brief Getter of the calibration values.
     * @return Current calibration values.
     */
    virtual Common::FloatAxisVector getOffset() const
    {
        return Common::FloatAxisVector();
    }

    /**
     * @brief Setter of the calibration values.
     * @param offset Calibration values (offset) to set.
     */
    virtual void setOffset(Common::FloatAxisVector offset)
    {
    }


private:
    /**
     * @brief Communicate with the sensor and initialze it.
     * @return whether initialization was successful or not.
     */
    virtual bool initSensor() = 0;
};


#endif

