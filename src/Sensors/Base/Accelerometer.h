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
    Common::vector3Float offset;
    Common::vector3Float scale;

public:
    Accelerometer()
        : Sensor(Sensor::SensorTypes::ACCELEROMETER)
    {
    }
    
    virtual ~Accelerometer() {}

    Common::vector3Float getAccOffset() {
        return offset;
    }

    Common::vector3Float getAccScale() {
        return scale;
    }

    void setAccCalibration(const Common::vector3Float& offset, const Common::vector3Float& scale) {
        this->offset = offset;
        this->scale = scale;
    }

    /**
     * @brief Get normalized accelerometer data (1 for 1g).  
     */
    Common::vector3Float getAcc_norm() {
        return (getAcc_norm_priv() - offset) * scale;
    }

    /**
     * @brief Get normalized accelerometer X axis (1 for 1g).
     */
    float getAccX_norm() {
        return (getAcc_norm_priv().x - offset.x) * scale.x;
    }

    /**
     * @brief Get normalized accelerometer Y axis (1 for 1g).
     */
    float getAccY_norm() {
        return (getAcc_norm_priv().y - offset.y) * scale.y;
    }

    /**
     * @brief Get normalized accelerometer Z axis (1 for 1g).
     */
    float getAccZ_norm() {
        return (getAcc_norm_priv().z - offset.z) * scale.z;
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
