/**
 * @file Sensor.h
 * @author Jan Wielgus
 * @brief Base class for all sensor classes.
 * @date 2020-11-25
 * 
 */

#ifndef SENSOR_H
#define SENSOR_H

#include "../Common/FloatAxesVector.h"
#include "SensorsMediator.h"


class Sensor
{
protected:
    SensorsMediator& sensorsMediator;
    bool initResultFlag = false; // TODO: change name to initResultFlag

public:
    Sensor(SensorsMediator& _sensorsMediator)
        : sensorsMediator(_sensorsMediator)
    {
    }

    virtual ~Sensor() {}

    /**
     * @brief Initialize the sensor.
     * Set initResultFlag here (true if initialized successfully)!
     * @return false if sensor wasn't initialized successfully,
     * returns true otherwise.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Check if sensor was initialized with good result and if
     * is working at the moment.
     * @return if initialize() method returned false or sensor
     * is not working.
     */
    virtual bool isGood() const
    {
        return initResultFlag;
    }

    /**
     * @brief After calling this method sensor will begin calibration during
     * it's normal execution and after that it will apply new offset values.
     * @param amtOfSamples Amount of samples that for example are averaged during calibration
     * (bigger amount -> longer calibration process and better results).
     * @return Amount of seconds that the calibration process will take.
     * You can call getOffset() method after that time and get new offset values.
     */
    virtual uint16_t startBackgroundCalibration(uint16_t amtOfSamples) = 0;

    /**
     * @brief Getter of the calibration values.
     * @return Current calibration values.
     */
    virtual FloatAxisVector getOffset() const = 0;

    /**
     * @brief Setter of the calibration values.
     * @param offset Calibration values (offset) to set.
     */
    virtual void setOffset(FloatAxisVector offset) = 0;

    // TODO: create sensor name getter
};


#endif

