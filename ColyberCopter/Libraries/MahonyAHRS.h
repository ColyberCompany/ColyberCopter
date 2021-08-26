/**
 * @file MahonyAHRS.h
 * @author Jan Wielgus
 * @brief
 * Madgwick's implementation of Mayhony's AHRS algorithm.
 * See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
 * 
 * Date			Author			Notes
 * 29/09/2011	SOH Madgwick    Initial release
 * 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
 * 
 * @date 2021-08-18
 */

#ifndef __MAHONYAHRS_H__
#define __MAHONYAHRS_H__


class MahonyAHRS
{
public:
    struct Quaternion
    {
        float r = 1.0f; // q0
        float i = 0.0f; // q1
        float j = 0.0f; // q2
        float k = 0.0f; // q3
    };

private:
    const float invSampleFreq; // interval / delta time

    volatile float twoKp;    // 2 * proportional gain (Kp)
    volatile float twoKi;    // 2 * integral gain (Ki)

    Quaternion quaternion;

    volatile float integralFBx = 0.0f, integralFBy = 0.0f, integralFBz = 0.0f;  // integral error terms scaled by Ki


public:
    MahonyAHRS(float interval, float Kp = 0.5f, float Ki = 0.0f);

    Quaternion mahonyAHRSUpdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    Quaternion mahonyAHRSUpdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
};


#endif // __MAHONYAHRS_H__
