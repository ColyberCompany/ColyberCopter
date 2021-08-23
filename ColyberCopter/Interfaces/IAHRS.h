/**
 * @file IAHRS.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Inteface for class that provide all calculated atitude measurements.
 * @date 2021-02-24
 * 
 */

#ifndef IAHRS_H
#define IAHRS_H

#include "../Common/Vector3.h"
#include "../Common/Quaternion.h"


namespace Interfaces
{
    class IAHRS
    {
    public:
        virtual ~IAHRS() {}

        // TODO: add brief to all methods

        virtual float getPitch_deg() = 0;
        virtual float getRoll_deg() = 0;
        virtual float getHeading_deg() = 0;
        //virtual float getYaw_deg() = 0;
        virtual Common::Quaternion getQuaternion() = 0;

        virtual double getLongitude_deg() = 0;
        virtual double getLatitude_deg() = 0;

        /**
         * @brief Height over the sea level getter.   
         */
        virtual float getAltitude_m() = 0; // TODO: check if AHRS return correct value
        virtual void resetAltitude() = 0;

        virtual Common::vector3Float getAngles_deg() = 0; // TODO: use this method where all 3 axes are needed
        virtual Common::vector3Double getPosition() = 0; // TODO: use this method where all 3 axes are needed
        virtual Common::vector3Float getAbsoluteAcceleration() = 0;
    };
}


#endif
