/**
 * @file INS.h
 * @author Jan Wielgus
 * @brief Inertial Navigation System.
 * @date 2021-08-26
 */

#ifndef __INS_H__
#define __INS_H__

#include "Common/Quaternion.h"
#include "Common/Constants.h"
#include "config.h"
#include <Fusion.h>
#include <IExecutable.h>
#include <AverageFilter.h>


/**
 * @brief Inertial Navigation System.
 * Keeps track of all angles, position and more.
 */
class INS : public IExecutable
{
    FusionBias fusionBias;
    FusionAhrs fusionAhrs;

// measurements:
    Common::Quaternion quaternion = {};
    Common::vector3Float angles_deg = {};
    double latitude_deg = 0.f;
    double longitude_deg = 0.f;
    float altitude_m = 0.f;
    Common::vector3Float earthAcceleration_mps2 = {};

// helper stuff:
    float refPressure = 1023.f; // reference pressure (pressure from which altitude is calculated)
    float baroRangefinderAltDiff = 0.f;
    static const uint8_t rangefinderUpdateFrequency = 6;
    static const uint16_t rfdrSmplsToAvg = Config::MainFrequency_Hz / rangefinderUpdateFrequency;
    AverageFilter<float, rfdrSmplsToAvg> rangefinderHeightFilter;

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
        return angles_deg * Common::Consts::DegToRad;
    }

    Common::vector3Float getAngles_deg() {
        return angles_deg;
    }

    float getPitch_deg() {
        return angles_deg.x;
    }

    float getRoll_deg() {
        return angles_deg.y;
    }

    float getHeading_deg() { // also yaw
        return angles_deg.z;
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

// Other:

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
    bool resetBaroAltitude();


// Values update:
    void updateAHRS();
    void udpateAltitude();
    void updateLatLong();
};


#endif // __INS_H__
