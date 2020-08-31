/**
 * @file MadgwickBase.h
 * @author Jan Wielgus
 * @brief Base class for Madgwick IMU and AHRS classes.
 * @date 2020-08-31
 * 
 */

#ifndef MADGWICKBASE_H
#define MADGWICKBASE_H


class MadgwickBase
{
protected:
    static const float DefaultBeta;
	float beta; // algorithm gain (2 * proportional gain)

	float q0;
	float q1;
	float q2;
	float q3; // quaternion of sensor frame relative to auxiliary frame
	float invSampleFreq;

	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;

public:
    MadgwickBase(float sampleFrequency, float beta = DefaultBeta);
    virtual ~MadgwickBase();

    /**
     * @brief Fast inverse square-root
     * See: http://en.wikipedia.org/wiki/Fast_inverse_square_root.
     * 
     * @param x Number which square root will be extracted.
     * @return Square root of parameter x.
     */
    static float invSqrt(float x);
};


#endif
