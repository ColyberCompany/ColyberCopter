/**
 * @file IRotationCalculation.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IROTATIONCALCULATION_H
#define IROTATIONCALCULATION_H

#include "Common/Vector3.h"
#include "Common/Quaternion.h"


namespace Interfaces
{
    class IRotationCalculation
    {
    public:
        virtual ~IRotationCalculation() {}

        virtual void updateRotationCalculation() = 0;
        virtual Common::Quaternion getQuaternion() = 0;

        virtual Common::vector3Float getAngles_deg()
        {
            auto ang_rad = getAngles_rad();
            return {
                ang_rad.x * 57.29578f,
                ang_rad.y * 57.29578f,
                ang_rad.z * 57.29578f
            };
        }

        virtual Common::vector3Float getAngles_rad()
        {
            auto q = getQuaternion();
            float q0 = q.r;
            float q1 = q.i;
            float q2 = q.j;
            float q3 = q.k;
            return {
                asinf(-2.0f * (q1 * q3 - q0 * q2)),
                atan2f(q0 * q1 + q2 * q3, 0.5f - q1 * q1 - q2 * q2),
                atan2f(q1 * q2 + q0 * q3, 0.5f - q2 * q2 - q3 * q3)
            };
        }
    };
}


#endif
