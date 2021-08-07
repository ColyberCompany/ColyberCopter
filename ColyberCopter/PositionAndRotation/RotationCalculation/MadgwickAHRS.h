/**
 * @file MadgwickAHRS.h
 * @author Jan Wielgus
 * @brief Implementation of Madgwick algorithm that use gyro, accelerometer and
 * magnetometer to calculate all rotation angles.
 * @date 2020-09-01
 * 
 */

#ifndef MADGWICKAHRS_H
#define MADGWICKAHRS_H

#include "MadgwickBase.h"
#include "../../Interfaces/IRotationCalculation.h"
#include "../../Interfaces/ISensorsData.h"


class MadgwickAHRS : protected MadgwickBase, public Interfaces::IRotationCalculation
{
private:
    float hx, hy;
	float _2q0mx, _2q0my, _2q0mz, _2q1mx,
	    _2bx, _2bz, _4bx, _4bz,
		_2q0, _2q1, _2q2, _2q3,
		_2q0q2, _2q2q3,
		q0q0, q0q1, q0q2, q0q3,
		q1q1, q1q2, q1q3,
		q2q2, q2q3, q3q3;
    

    Common::vector3Float angles_deg; // x-pitch, y-roll, z-yaw
    Common::vector3Float angles_rad; // x-pitch, y-roll, z-yaw
    Interfaces::ISensorsData* sensorsData;

    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;


public:
    MadgwickAHRS(Interfaces::ISensorsData* sensorData, float sampleFrequency, float beta = DefaultBeta);
    void updateRotationCalculation() override;
    Common::vector3Float getAngles_deg() override;
    Common::vector3Float getAngles_rad() override;
};


#endif
