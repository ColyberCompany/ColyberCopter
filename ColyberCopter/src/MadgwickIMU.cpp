/**
 * @file MadgwickIMU.cpp
 * @author Jan Wielgus
 * @date 2020-08-31
 * 
 */

#include "../PositionAndRotation/RotationCalculation/MadgwickIMU.h"

using Interfaces::ISensorsData;
using Common::vector3Float;


MadgwickIMU::MadgwickIMU(ISensorsData& _sensorsData, float sampleFrequency, float beta)
    : MadgwickBase(sampleFrequency, beta),
	sensorsData(_sensorsData)
{
    _2q0 = _2q1 = _2q2 = _2q3 = 0;
	_4q0 = _4q1 = _4q2 = 0;
	_8q1 = _8q2 = 0;
	q0q0 = q1q1 = q2q2 = q3q3 = 0;
}


void MadgwickIMU::updateRotationCalculation()
{
    // Convert gyroscope degrees/sec to radians/sec
    vector3Float rawGyro = sensorsData.getGyro_degPerSec();
	gx = rawGyro.x * 0.0174533f;
	gy = rawGyro.y * 0.0174533f;
	gz = rawGyro.z * 0.0174533f;

    vector3Float normAcc = sensorsData.getAcc_normVector();
    ax = normAcc.x;
    ay = normAcc.y;
    az = normAcc.z;

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	//if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) // Should never occur, so skip
	{
		// Normalise accelerometer measurement.
        /* Skip, accelerometer measurements are already normalized
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm; */

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_4q0 = 4.0f * q0;
		_4q1 = 4.0f * q1;
		_4q2 = 4.0f * q2;
		_8q1 = 8.0f * q1;
		_8q2 = 8.0f * q2;
		q0q0 = q0 * q0;
		q1q1 = q1 * q1;
		q2q2 = q2 * q2;
		q3q3 = q3 * q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * invSampleFreq;
	q1 += qDot2 * invSampleFreq;
	q2 += qDot3 * invSampleFreq;
	q3 += qDot4 * invSampleFreq;

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;



	// Compute angles

	// in radians
	angles_rad.y = atan2f(q0 * q1 + q2 * q3, 0.5f - q1 * q1 - q2 * q2);
	angles_rad.x = asinf(-2.0f * (q1 * q3 - q0 * q2));
	angles_rad.z = atan2f(q1 * q2 + q0 * q3, 0.5f - q2 * q2 - q3 * q3);

    // in degrees
    angles_deg.x = angles_rad.x * 57.29578f;
    angles_deg.y = angles_rad.y * 57.29578f;
    angles_deg.z = angles_rad.z * 57.29578f;
    angles_deg.z += 180;
}


vector3Float MadgwickIMU::getAngles_deg()
{
    return angles_deg;
}


vector3Float MadgwickIMU::getAngles_rad()
{
    return angles_rad;
}
