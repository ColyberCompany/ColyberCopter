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
    Common::vector3Float offset;

public:
    Gyroscope()
        : Sensor(Sensor::SensorTypes::GYROSCOPE)
    {
    }

    virtual ~Gyroscope() {}

    Common::vector3Float getGyroOffset() {
        return offset;
    }

    void setGyroOffset(const Common::vector3Float& offset) {
        this->offset = offset;
    }

    /**
     * @brief Get angular rotation in deg/sec.
     */
    Common::vector3Float getGyro_dps() {
        return getGyro_dps_priv() - offset;
    }

    /**
     * @brief Get angular rotation on X axis in deg/sec.
     */
    float getGyroX_dps() {
        return getGyro_dps_priv().x - offset.x;
    }

    /**
     * @brief Get angular rotation on X axis in deg/sec.
     */
    float getGyroY_dps() {
        return getGyro_dps_priv().y - offset.y;
    }

    /**
     * @brief Get angular rotation on X axis in deg/sec.
     */
    float getGyroZ_dps() {
        return getGyro_dps_priv().z - offset.z;
    }


    /**
     * @brief Get angular rotation in rad/sec.
     */
    Common::vector3Float getGyro_rps() {
        return getGyro_dps() * Common::Consts::DegToRad;
    }

    /**
     * @brief Get angular rotation on X axis in rad/sec.
     */
    float getGyroX_rps() {
        return getGyroX_dps() * Common::Consts::DegToRad;
    }

    /**
     * @brief Get angular rotation on Y axis in rad/sec.
     */
    float getGyroY_rps() {
        return getGyroY_dps() * Common::Consts::DegToRad;
    }

    /**
     * @brief Get angular rotation on Z axis in rad/sec.
     */
    float getGyroZ_rps() {
        return getGyroZ_dps() * Common::Consts::DegToRad;
    }

private:
    /**
     * @brief Get angular rotation in deg/sec.
     */
    virtual Common::vector3Float getGyro_dps_priv() = 0;
};


#endif // __GYROSCOPE_H__
