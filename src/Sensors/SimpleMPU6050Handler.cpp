/**
 * @file SimpleMPU6050Handler.cpp
 * @author Jan Wielgus
 * @date 2021-08-12
 */

#include "SimpleMPU6050Handler.h"
#include "config.h"
#include "calibration.h"

constexpr float AccLPFCutOffFreq = 7.f;
// constexpr float GyroLPFCutOffFreq = 10.f;


SimpleMPU6050Handler::SimpleMPU6050Handler()
    : accLPF(
        {AccLPFCutOffFreq, Config::MainInterval_s},
        {AccLPFCutOffFreq, Config::MainInterval_s},
        {AccLPFCutOffFreq, Config::MainInterval_s}
    )
{
    setAccCalibration(Calibration::AccOffset, Calibration::AccScale);
    setGyroOffset(Calibration::GyroOffset);
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
