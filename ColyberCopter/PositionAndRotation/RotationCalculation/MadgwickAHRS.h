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

#include "../../Interfaces/IRotationCalculation.h"


class MadgwickAHRS : public Interfaces::IRotationCalculation
{
    static const float DefaultBeta;

    const float beta;
    const float invSampleFreq;

    float q0 = 1.0f;
    float q1 = 0.0f;
    float q2 = 0.0f;
    float q3 = 0.0f;

public:
    MadgwickAHRS(float beta = DefaultBeta);

    void updateRotationCalculation() override;
    Common::vector3Float getAngles_deg() override;
    Common::vector3Float getAngles_rad() override;

private:
    void madgwickAHRSUpdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    void madgwickAHRSUpdateIMU(float gx, float gy, float gz, float ax, float ay, float az);

    /**
     * @brief Fast inverse square-root
     * See: http://en.wikipedia.org/wiki/Fast_inverse_square_root.
     * @param x Number which square root will be extracted.
     * @return Square root of parameter x.
     */
    static float invSqrt(float x);
};


#endif
