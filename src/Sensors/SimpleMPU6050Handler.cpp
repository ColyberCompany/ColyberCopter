/**
 * @file SimpleMPU6050Handler.cpp
 * @author Jan Wielgus
 * @date 2021-08-12
 */

#include "SimpleMPU6050Handler.h"
#include "Common/Vector3.h"
#include "config.h"

constexpr float AccLPFCutOffFreq = 8.f;
// constexpr float GyroLPFCutOffFreq = 10.f;

// TODO: perform full calibration (instructions in video; link in Accelerometer.h)
constexpr FusionVector AccOffset = {0.017505502, 0.004973429, 0.026660183};
constexpr FusionVector AccScale = {0.99603490, 0.99502618, 0.98504321};
constexpr FusionVector GyroOffset = {-2.0812696,  1.9969787, -0.2270786};


SimpleMPU6050Handler::SimpleMPU6050Handler()
    : accLPF(
        {AccLPFCutOffFreq, Config::MainInterval_s},
        {AccLPFCutOffFreq, Config::MainInterval_s},
        {AccLPFCutOffFreq, Config::MainInterval_s}
    )
{
    accelerometer().setCalibration(CalibrationIntertial::Calibration{
        .sensitivity = AccScale,
        .offset = AccOffset
    });
    gyroscope().setCalibration(CalibrationIntertial::Calibration{
        .offset = GyroOffset
    });
}


bool SimpleMPU6050Handler::init_priv()
{
    if (Accelerometer::isInitialized() || Gyroscope::isInitialized())
        return true;

    if (!mpu.initialize())
        return false;
        
    mpu.enableCompassBypass();

    return true;
}


void SimpleMPU6050Handler::execute()
{
    mpu.readRawData();

    auto accNorm = mpu.getNormalizedAcceleration();
    // accFiltered = Common::vector3Float(accNorm.x, accNorm.y, accNorm.z); // version without lpf filter
    accFiltered = Common::vector3Float(
        accLPF.x.update(accNorm.x),
        accLPF.y.update(accNorm.y),
        accLPF.z.update(accNorm.z)
    );

    gyroFiltered = Common::vector3Float(mpu.getNormalizedRotation());
}
