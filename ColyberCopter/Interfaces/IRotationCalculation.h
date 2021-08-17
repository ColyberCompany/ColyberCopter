/**
 * @file IRotationCalculation.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IROTATIONCALCULATION_H
#define IROTATIONCALCULATION_H

#include "../Common/Vector3.h"
#include "../Common/Quaternion.h"


namespace Interfaces
{
    class IRotationCalculation
    {
    public:
        virtual ~IRotationCalculation() {}

        virtual void updateRotationCalculation() = 0;
        virtual Common::vector3Float getAngles_deg() = 0;
        virtual Common::vector3Float getAngles_rad() = 0;
        virtual Common::Quaternion getQuaternion() = 0;
    };
}


#endif
