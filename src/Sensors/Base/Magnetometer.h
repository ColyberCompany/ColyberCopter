/**
 * @file Magnetometer.h
 * @author Jan Wielgus
 * @brief Base class for all magnetometers.
 * @date 2021-08-11
 */

#ifndef __MAGNETOMETER_H__
#define __MAGNETOMETER_H__

#include "Sensor.h"
#include "Common/Vector3.h"
#include "CalibrationMagnetic.h"


class Magnetometer : public Sensor, public CalibrationMagnetic
{
public:
    Magnetometer()
        : Sensor(Sensor::SensorTypes::MAGNETOMETER)
    {
    }

    virtual ~Magnetometer() {}

    /**
     * @brief Current instance as magnetometer.
     */
    Magnetometer& magnometer() {
        return *this;
    }

    Common::vector3Float getMagn_norm() {
        return applyCalibration(getMagn_norm_priv());
    }

private:
    virtual Common::vector3Float getMagn_norm_priv() = 0;
};


#endif // __MAGNETOMETER_H__
