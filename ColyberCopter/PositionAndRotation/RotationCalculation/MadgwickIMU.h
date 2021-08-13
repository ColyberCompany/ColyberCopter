/**
 * @file MadgwickIMU.h
 * @author Jan Wielgus
 * @brief Madgwick algorithm implementation that use only gyro and accelerometer.
 * @date 2020-08-31
 * 
 */

#ifndef MADGWICKIMU_H
#define MADGWICKIMU_H

#include "MadgwickBase.h"
#include "../../Interfaces/IRotationCalculation.h"


class MadgwickIMU : protected MadgwickBase, public Interfaces::IRotationCalculation
{
private:
    float _2q0, _2q1, _2q2, _2q3,
        _4q0, _4q1, _4q2,
        _8q1, _8q2,
        q0q0, q1q1, q2q2, q3q3;


    Common::vector3Float angles_deg; // x-pitch, y-roll, z-yaw
    Common::vector3Float angles_rad; // x-pitch, y-roll, z-yaw

    float ax, ay, az;
    float gx, gy, gz;


public:
    MadgwickIMU(float sampleFrequency, float beta = DefaultBeta);
    void updateRotationCalculation() override;
    Common::vector3Float getAngles_deg() override;
    Common::vector3Float getAngles_rad() override;
};


#endif
