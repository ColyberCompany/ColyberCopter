/**
 * @file MadgwickBase.cpp
 * @author Jan Wielgus
 * @date 2020-08-31
 * 
 */

#include "PositionAndRotation/RotationCalculation/MadgwickBase.h"


const float MadgwickBase::DefaultBeta = 0.1;


MadgwickBase::MadgwickBase(float sampleFrequency, float beta)
{
    invSampleFreq = 1.0f / sampleFrequency;
    this->beta = beta;
    q0 = 1.0f;
	q1 = 0.0f;
	q2 = 0.0f;
	q3 = 0.0f;
}


MadgwickBase::~MadgwickBase()
{
}


float MadgwickBase::invSqrt(float x)
{
    float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	y = y * (1.5f - (halfx * y * y));
	return y;
}
