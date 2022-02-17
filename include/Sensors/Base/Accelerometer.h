/**
 * @file Accelerometer.h
 * @author Jan Wielgus
 * @brief Base class for all accelerometers.
 * @date 2021-08-11
 */

#ifndef __ACCELEROMETER_H__
#define __ACCELEROMETER_H__

#include "Sensor.h"
#include "../../Common/Vector3.h"
#include "../../Common/Constants.h"


class Accelerometer : public Sensor
{
public:
    Accelerometer()
        : Sensor(Enums::SensorTypes::ACCELEROMETER)
    {
    }
    
    virtual ~Accelerometer() {}

    /**
     * @brief Get normalized accelerometer data (1 for 1g).  
     */
    virtual Common::vector3Float get_norm() = 0;

    /**
     * @brief Get normalized accelerometer X axis (1 for 1g).
     */
    virtual float getX_norm() = 0;

    /**
     * @brief Get normalized accelerometer Y axis (1 for 1g).
     */
    virtual float getY_norm() = 0;

    /**
     * @brief Get normalized accelerometer Z axis (1 for 1g).
     */
    virtual float getZ_norm() = 0;


    /**
     * @brief Get accelerometer data in m/s^2 (9.81 for 1g).
     */
    Common::vector3Float get_mps2() {
        Common::vector3Float acc = get_norm();
        return {
            acc.x * Common::Consts::GravitationalAcceleration,
            acc.y * Common::Consts::GravitationalAcceleration,
            acc.z * Common::Consts::GravitationalAcceleration
        };
    }

    /**
     * @brief Get accelerometer X axis in m/s^2 (9.81 for 1g).
     */
    float getX_mps2() {
        return getX_norm() * Common::Consts::GravitationalAcceleration;
    }

    /**
     * @brief Get accelerometer Y axis in m/s^2 (9.81 for 1g).
     */
    float getY_mps2() {
        return getY_norm() * Common::Consts::GravitationalAcceleration;
    }

    /**
     * @brief Get accelerometer Z axis in m/s^2 (9.81 for 1g).
     */
    float getZ_mps2() {
        return getZ_norm() * Common::Consts::GravitationalAcceleration;
    }

};


#endif // __ACCELEROMETER_H__
