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


class Gyroscope : public Sensor
{
public:
    Gyroscope()
        : Sensor(Sensor::SensorTypes::GYROSCOPE)
    {
    }

    virtual ~Gyroscope() {}

    /**
     * @brief Get angular rotation in deg/sec.
     */
    virtual Common::vector3Float get_degPerSec() = 0;

    /**
     * @brief Get angular rotation on X axis in deg/sec.
     */
    virtual float getX_degPerSec() = 0;

    /**
     * @brief Get angular rotation on X axis in deg/sec.
     */
    virtual float getY_degPerSec() = 0;

    /**
     * @brief Get angular rotation on X axis in deg/sec.
     */
    virtual float getZ_degPerSec() = 0;


    /**
     * @brief Get angular rotation in rad/sec.
     */
    Common::vector3Float get_radPerSec() {
        Common::vector3Float gyro = get_degPerSec();
        return {
            gyro.x * Common::Consts::DegToRad,
            gyro.y * Common::Consts::DegToRad,
            gyro.z * Common::Consts::DegToRad
        };
    }

    /**
     * @brief Get angular rotation on X axis in rad/sec.
     */
    float getX_radPerSec() {
        return getX_degPerSec() * Common::Consts::DegToRad;
    }

    /**
     * @brief Get angular rotation on Y axis in rad/sec.
     */
    float getY_radPerSec() {
        return getY_degPerSec() * Common::Consts::DegToRad;
    }

    /**
     * @brief Get angular rotation on Z axis in rad/sec.
     */
    float getZ_radPerSec() {
        return getZ_degPerSec() * Common::Consts::DegToRad;
    }
};


#endif // __GYROSCOPE_H__
