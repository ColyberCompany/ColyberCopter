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

class Accelerometer : public Sensor
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
    Accelerometer()
        : Sensor(Sensor::SensorTypes::ACCELEROMETER)
    {
    }
    
    virtual ~Accelerometer() {}

    Calibration getCalibration() {
        return calibration;
    }

    void setCalibration(const Calibration& calibration) {
        this->calibration = calibration;
    }

    /**
     * @brief Get normalized accelerometer data (1 for 1g).  
     */
    Common::vector3Float getAcc_norm() {
        return (getAcc_norm_priv() - calibration.offset) * calibration.scale;
    }

    /**
     * @brief Get normalized accelerometer X axis (1 for 1g).
     */
    float getAccX_norm() {
        return (getAcc_norm_priv().x - calibration.offset.x) * calibration.scale.x;
    }

    /**
     * @brief Get normalized accelerometer Y axis (1 for 1g).
     */
    float getAccY_norm() {
        return (getAcc_norm_priv().y - calibration.offset.y) * calibration.scale.y;
    }

    /**
     * @brief Get normalized accelerometer Z axis (1 for 1g).
     */
    float getAccZ_norm() {
        return (getAcc_norm_priv().z - calibration.offset.z) * calibration.scale.z;
    }


    /**
     * @brief Get accelerometer data in m/s^2 (9.81 for 1g).
     */
    Common::vector3Float getAcc_mps2() {
        return getAcc_norm() * Common::Consts::GravitationalAcceleration;
    }

    /**
     * @brief Get accelerometer X axis in m/s^2 (9.81 for 1g).
     */
    float getAccX_mps2() {
        return getAccX_norm() * Common::Consts::GravitationalAcceleration;
    }

    /**
     * @brief Get accelerometer Y axis in m/s^2 (9.81 for 1g).
     */
    float getAccY_mps2() {
        return getAccY_norm() * Common::Consts::GravitationalAcceleration;
    }

    /**
     * @brief Get accelerometer Z axis in m/s^2 (9.81 for 1g).
     */
    float getAccZ_mps2() {
        return getAccZ_norm() * Common::Consts::GravitationalAcceleration;
    }

private:
    /**
     * @brief Get normalized accelerometer data (1 for 1g).  
     */
    virtual Common::vector3Float getAcc_norm_priv() = 0;
};


#endif // __ACCELEROMETER_H__
