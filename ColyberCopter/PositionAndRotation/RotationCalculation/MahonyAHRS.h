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

#include "../../Interfaces/IRotationCalculation.h"

#define twoKpDef    (2.0f * 0.5f)   // 2 * proportional gain
#define twoKiDef    (2.0f * 0.0f)   // 2 * integral gain


class MahonyAHRS : public Interfaces::IRotationCalculation
{
    const float invSampleFreq;

    volatile float twoKp = twoKpDef;    // 2 * proportional gain (Kp)
    volatile float twoKi = twoKiDef;    // 2 * integral gain (Ki)

    volatile float q0 = 1.0f;
    volatile float q1 = 0.0f;
    volatile float q2 = 0.0f;
    volatile float q3 = 0.0f;

    volatile float integralFBx = 0.0f, integralFBy = 0.0f, integralFBz = 0.0f;  // integral error terms scaled by Ki


public:
    MahonyAHRS();

    void updateRotationCalculation() override;
    Common::Quaternion getQuaternion() override;

private:
    void mahonyAHRSUpdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    void mahonyAHRSUpdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
};


#endif // __MAHONYAHRS_H__
