/**
 * @file MadgwickAHRS.h
 * @author Jan Wielgus
 * @brief
 * Implementation of Madgwick's IMU and AHRS algorithms.
 * See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
 * 
 * Date			Author          Notes
 * 29/09/2011	SOH Madgwick    Initial release
 * 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
 * 19/02/2012	SOH Madgwick	Magnetometer measurement is normalised
 * 
 * @date 2020-09-01
 */

#ifndef MADGWICKAHRS_H
#define MADGWICKAHRS_H


class MadgwickAHRS
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
    static const float DefaultBeta;

    const float beta;
    const float invSampleFreq;  // interval / delta time

    Quaternion quaternion;


public:
    MadgwickAHRS(float interval, float beta = DefaultBeta);

    Quaternion madgwickAHRSUpdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    Quaternion madgwickAHRSUpdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
};


#endif
