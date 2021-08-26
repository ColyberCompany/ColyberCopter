/**
 * @file INS.h
 * @author Jan Wielgus
 * @brief Inertial Navigation System.
 * @date 2021-08-26
 */

#ifndef __INS_H__
#define __INS_H__

#include "../Common/Quaternion.h"


class INS
{


public:
    INS();

// Rotation:

    Common::Quaternion getQuaternion();
    Common::vector3Float getAngles_rad();
    Common::vector3Float getAngles_deg();
    float getPitch_deg();
    float getRoll_deg();
    float getHeading_deg(); // also yaw

// Position:

    /**
     * @brief Get position on the world:
     * x (latitude) and y (longitude) in degrees,
     * z (altitude) in meters.
     */
    Common::vector3Double getPosition();
    double getLongitude_deg();
    double getLatitude_deg();
};


#endif // __INS_H__
