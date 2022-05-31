/**
 * @file Accelerometer.h
 * @author Jan Wielgus
 * @brief Base class for all accelerometers.
 * @date 2021-08-11
 */

#ifndef __ACCELEROMETER_H__
#define __ACCELEROMETER_H__

#include "Sensor.h"
#include "Common/Vector3.h"
#include "Common/Constants.h"
#include "CalibrationIntertial.h"


class Accelerometer : public Sensor, public CalibrationIntertial
{
public:
    Accelerometer()
        : Sensor(Sensor::SensorTypes::ACCELEROMETER)
    {
    }
    
    virtual ~Accelerometer() {}

    /**
     * @brief Current instance as accelerometer.
     */
    Accelerometer& accelerometer() {
        return *this;
    }

    /**
     * @brief Get normalized accelerometer data (1 for 1g).  
     */
    Common::vector3Float getAcc_norm() {
        return applyCalibration(getAcc_norm_priv());
    }

    /**
     * @brief Get accelerometer data in m/s^2 (9.81 for 1g).
     */
    Common::vector3Float getAcc_mps2() {
        return getAcc_norm() * Common::Consts::GravitationalAcceleration;
    }

private:
    /**
     * @brief Get normalized accelerometer data (1 for 1g).  
     */
    virtual Common::vector3Float getAcc_norm_priv() = 0;
};


#endif // __ACCELEROMETER_H__
