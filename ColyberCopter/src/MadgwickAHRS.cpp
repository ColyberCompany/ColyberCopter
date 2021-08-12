/**
 * @file MadgwickAHRS.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "../PositionAndRotation/RotationCalculation/MadgwickAHRS.h"
#include "../Instances/SensorInstances.h"

using Common::vector3Float;

MadgwickAHRS::MadgwickAHRS(float sampleFrequency, float beta)
    : MadgwickBase(sampleFrequency, beta)
{
    hx = hy = 0;
	_2q0mx = _2q0my = _2q0mz = _2q1mx = 0;
	_2bx = _2bz = _4bx = _4bz = 0;
	_2q0 = _2q1 = _2q2 = _2q3 = 0;
	_2q0q2 = _2q2q3 = 0;
	q0q0 = q0q1 = q0q2 = q0q3 = 0;
	q1q1 = q1q2 = q1q3 = 0;
	q2q2 = q2q3 = q3q3 = 0;
}


void MadgwickAHRS::updateRotationCalculation()
{
    auto gyro_degPerSec = Instance::gyro.get_degPerSec();
	// Convert gyroscope degrees/sec to radians/sec
	gx = gyro_degPerSec.x * 0.0174533f;
	gy = gyro_degPerSec.y * 0.0174533f;
	gz = gyro_degPerSec.z * 0.0174533f;

	auto acc_norm = Instance::acc.get_norm();
    ax = acc_norm.x;
    ay = acc_norm.y;
    az = acc_norm.z;

	auto mag_norm = Instance::magn.get_norm();
    mx = mag_norm.x;
    my = mag_norm.y;
    mz = mag_norm.z;

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	//if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) // Should never occur, so skip
	{
		// Normalise accelerometer measurement
        /* Skip, accelerometer measurements are already normalized
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;*/

		// Normalise magnetometer measurement
        /* Skip, magnetometer measurements are already normalized
		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
		mx *= recipNorm;
		my *= recipNorm;
		mz *= recipNorm;*/

		// Auxiliary variables to avoid repeated arithmetic
		_2q0mx = 2.0f * q0 * mx;
		_2q0my = 2.0f * q0 * my;
		_2q0mz = 2.0f * q0 * mz;
		_2q1mx = 2.0f * q1 * mx;
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_2q0q2 = 2.0f * q0 * q2;
		_2q2q3 = 2.0f * q2 * q3;
		q0q0 = q0 * q0;
		q0q1 = q0 * q1;
		q0q2 = q0 * q2;
		q0q3 = q0 * q3;
		q1q1 = q1 * q1;
		q1q2 = q1 * q2;
		q1q3 = q1 * q3;
		q2q2 = q2 * q2;
		q2q3 = q2 * q3;
		q3q3 = q3 * q3;

		// Reference direction of Earth's magnetic field
		hx = mx * q0q0 - _2q0my * q3 + _2q0mz * q2 + mx * q1q1 + _2q1 * my * q2 + _2q1 * mz * q3 - mx * q2q2 - mx * q3q3;
		hy = _2q0mx * q3 + my * q0q0 - _2q0mz * q1 + _2q1mx * q2 - my * q1q1 + my * q2q2 + _2q2 * mz * q3 - my * q3q3;
		_2bx = sqrtf(hx * hx + hy * hy);
		_2bz = -_2q0mx * q2 + _2q0my * q1 + mz * q0q0 + _2q1mx * q3 - mz * q1q1 + _2q2 * my * q3 - mz * q2q2 + mz * q3q3;
		_4bx = 2.0f * _2bx;
		_4bz = 2.0f * _2bz;

		// Gradient decent algorithm corrective step
		s0 = -_2q2 * (2.0f * q1q3 - _2q0q2 - ax) + _2q1 * (2.0f * q0q1 + _2q2q3 - ay) - _2bz * q2 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q3 + _2bz * q1) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q2 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s1 = _2q3 * (2.0f * q1q3 - _2q0q2 - ax) + _2q0 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q1 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + _2bz * q3 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q2 + _2bz * q0) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q3 - _4bz * q1) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s2 = -_2q0 * (2.0f * q1q3 - _2q0q2 - ax) + _2q3 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q2 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + (-_4bx * q2 - _2bz * q0) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q1 + _2bz * q3) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q0 - _4bz * q2) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s3 = _2q1 * (2.0f * q1q3 - _2q0q2 - ax) + _2q2 * (2.0f * q0q1 + _2q2q3 - ay) + (-_4bx * q3 + _2bz * q1) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q0 + _2bz * q2) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q1 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
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
	angles_rad.y = atan2f(q0 * q1 + q2 * q3, 0.5f - q1 * q1 - q2 * q2);		// roll
	angles_rad.x = asinf(-2.0f * (q1 * q3 - q0 * q2));						// pitch
	angles_rad.z = atan2f(q1 * q2 + q0 * q3, 0.5f - q2 * q2 - q3 * q3);		// roll (heading)

	// in degrees
    angles_deg.x = angles_rad.x * 57.29578f;
    angles_deg.y = angles_rad.y * 57.29578f;
    angles_deg.z = angles_rad.z * 57.29578f;
    angles_deg.z += 180;
}


vector3Float MadgwickAHRS::getAngles_deg()
{
    return angles_deg;
}


vector3Float MadgwickAHRS::getAngles_rad()
{
    return angles_rad;
}
