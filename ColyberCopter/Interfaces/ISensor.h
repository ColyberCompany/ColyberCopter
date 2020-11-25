/**
 * @file ISensor.h
 * @author Jan Wielgus
 * @brief Interface for all sensor classes.
 * @date 2020-11-25
 * 
 */

#ifndef ISENSOR_H
#define ISENSOR_H

#include "Common/FloatAxesVector.h"


namespace Interfaces
{
    class ISensor
    {
    public:
        virtual ~ISensor() {}

        /**
         * @brief Initialize the sensor.
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
        virtual bool isGood() const = 0; // TODO: try to figure out a better name

        /**
         * @brief After calling this method sensor will begin calibration during
         * it's normal execution and after that it will apply new offset values.
         * @param samplesToAverage Amount of samples to average during calibration
         * (bigger amount -> longer calibration process and better results).
         * @return Amount of seconds that the calibration process will take.
         * You can call getOffset() method after that time and get new offset values.
         */
        virtual uint16_t startBackgroundCalibration(int16_t samplesToAverage) = 0;

        /**
         * @brief Getter of the calibration values.
         * @return Current calibration values.
         */
        virtual const FloatAxisVector* getOffset() const = 0;

        /**
         * @brief Setter of the calibration values.
         * @param offset Calibration values (offset) to set.
         */
        virtual void setOffset(FloatAxisVector offset) = 0;
    };
}


#endif

