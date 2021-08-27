/**
 * @file INS.h
 * @author Jan Wielgus
 * @brief Inertial Navigation System.
 * @date 2021-08-26
 */

#ifndef __INS_H__
#define __INS_H__

#include "../Common/Quaternion.h"
#include "../Common/Constants.h"
#include "../Libraries/MadgwickAHRS.h"
#include <IExecutable.h>


/**
 * @brief Inertial Navigation System.
 * Keeps track of all angles, position and more.
 */
class INS : public IExecutable
{
// instances:
    MadgwickAHRS ahrs;

// measurements:
    Common::Quaternion quaternion = {};
    Common::vector3Float angles_rad = {};
    double latitude_deg = 0.f;
    double longitude_deg = 0.f;
    float altitude_m = 0.f;
    Common::vector3Float earthAcceleration_mps2 = {};

// helper variables:
    float refPressure = 1023.f; // reference pressure (pressure from which altitude is calculated)

// temp altitude calc:
    float verticalVelocity_mps = 0.f;
    float lastBaroAlt = 0.f;
    float complementaryBeta = 0.997f;

public:
    INS();

// Rotation:

    Common::Quaternion getQuaternion() {
        return quaternion;
    }

    Common::vector3Float getAngles_rad() {
        return angles_rad;
    }

    Common::vector3Float getAngles_deg() {
        return {
            angles_rad.x * Common::Consts::RadToDeg,
            angles_rad.y * Common::Consts::RadToDeg,
            angles_rad.z * Common::Consts::RadToDeg
        };
    }

    float getPitch_deg() {
        return angles_rad.x * Common::Consts::RadToDeg;
    }

    float getRoll_deg() {
        return angles_rad.y * Common::Consts::RadToDeg;
    }

    float getHeading_deg() { // also yaw
        return angles_rad.z * Common::Consts::RadToDeg;
    }

// Position:

    /**
     * @brief Get latitude in degrees (North is positive).
     */
    double getLatitude_deg() {
        return latitude_deg;
    }

    /**
     * @brief Get longitude in degrees (East is positive).
     */
    double getLongitude_deg() {
        return longitude_deg;
    }

    /**
     * @brief Get altitude from where the drone was powered on.
     */
    float getAltitude_m() {
        return altitude_m;
    }

// Calculated:

    /**
     * @brief Earth acceleration acceleration relative to earth in m/s^2
     * (if stationary then all axes are 0).
     */
    Common::vector3Float getEarthAcceleration_mps2() {
        return earthAcceleration_mps2;
    }

private:
    /**
     * @brief Updates everything.
     */
    void execute() override;

    /**
     * @brief Set reference pressure to current pressure reading.
     * Altitude for current position will equal 0.
     */
    bool resetAltitude();


// Values update:
    void updateQuaternionAndAngles();
    void updateEarthAcceleration();
    void udpateAltitude();
    void updateLatLong();
};


#endif // __INS_H__
