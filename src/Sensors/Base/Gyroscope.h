/**
 * @file Gyroscope.h
 * @author Jan Wielgus
 * @brief Base class for all gyroscopes.
 * @date 2021-08-11
 */

#ifndef __GYROSCOPE_H__
#define __GYROSCOPE_H__

#include "Sensor.h"
#include "Common/Vector3.h"
#include "Common/Constants.h"
#include "CalibrationIntertial.h"


class Gyroscope : public Sensor, public CalibrationIntertial
{
public:
    Gyroscope()
        : Sensor(Sensor::SensorTypes::GYROSCOPE)
    {
    }

    virtual ~Gyroscope() {}

    /**
     * @brief Current instance as gyroscope.
     */
    Gyroscope& gyroscope() {
        return *this;
    }

    /**
     * @brief Get angular rotation in deg/sec.
     */
    Common::vector3Float getGyro_dps() {
        return applyCalibration(getGyro_dps_priv());
    }

    /**
     * @brief Get angular rotation in rad/sec.
     */
    Common::vector3Float getGyro_rps() {
        return getGyro_dps() * Common::Consts::DegToRad;
    }

private:
    /**
     * @brief Get angular rotation in deg/sec.
     */
    virtual Common::vector3Float getGyro_dps_priv() = 0;
};


#endif // __GYROSCOPE_H__
