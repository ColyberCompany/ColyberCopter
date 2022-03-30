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


class Magnetometer : public Sensor
{
public:
    struct Calibration {
        Common::vector3Float offset;
        Common::vector3Float scale;

        Calibration() {}
        Calibration(float ox, float oy, float oz, float sx, float sy, float sz) :
            offset(ox, oy, oz), scale(sx, sy, sz)
        {}
    };

private:
    Calibration calibration;

public:
    Magnetometer()
        : Sensor(Sensor::SensorTypes::MAGNETOMETER)
    {
    }

    virtual ~Magnetometer() {}

    Calibration getCalibration() {
        return calibration;
    }

    void setCalibration(const Calibration& calibration) {
        this->calibration = calibration;
    }

    Common::vector3Float getMagn_norm() {
        return (getMagn_norm_priv() - calibration.offset) * calibration.scale;
    }

    float getX_norm() {
        return (getMagn_norm_priv().x - calibration.offset.x) * calibration.scale.x;
    }

    float getY_norm() {
        return (getMagn_norm_priv().y - calibration.offset.y) * calibration.scale.y;
    }

    float getZ_norm() {
        return (getMagn_norm_priv().z - calibration.offset.z) * calibration.scale.z;
    }

private:
    virtual Common::vector3Float getMagn_norm_priv() = 0;
};


#endif // __MAGNETOMETER_H__
