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

// Calibration: https://thecavepearlproject.org/2015/05/22/calibrating-any-compass-or-accelerometer-for-arduino/


class Magnetometer : public Sensor
{
    Common::vector3Float offset = {0, 0, 0};
    Common::vector3Float scale = {1.f, 1.f, 1.f};

public:
    Magnetometer()
        : Sensor(Sensor::SensorTypes::MAGNETOMETER)
    {
    }

    virtual ~Magnetometer() {}

    Common::vector3Float getMagnOffset() {
        return offset;
    }

    Common::vector3Float getMagnScale() {
        return scale;
    }

    void setMagnCalibration(const Common::vector3Float& offset, const Common::vector3Float& scale) {
        this->offset = offset;
        this->scale = scale;
    }

    Common::vector3Float getMagn_norm() {
        return (getMagn_norm_priv() - offset) * scale;
    }

private:
    virtual Common::vector3Float getMagn_norm_priv() = 0;
};


#endif // __MAGNETOMETER_H__
