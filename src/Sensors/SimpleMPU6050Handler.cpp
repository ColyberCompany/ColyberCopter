/**
 * @file SimpleMPU6050Handler.cpp
 * @author Jan Wielgus
 * @date 2021-08-12
 */

#include "SimpleMPU6050Handler.h"
#include "config.h"


SimpleMPU6050Handler::SimpleMPU6050Handler()
{
}


bool SimpleMPU6050Handler::init_priv()
{
    if (Accelerometer::isInitialized() || Gyroscope::isInitialized())
        return true;

    using Config::AccOffset;
    using Config::GyroOffset;

    bool initResult = mpu.initialize();
    config3AxisLPF(accLPF, Config::AccLPFCutOffFreq);
    mpu.setAccOffset(AccOffset.x, AccOffset.y, AccOffset.z);
    mpu.setGyroOffset(GyroOffset.x, GyroOffset.y, GyroOffset.z);
    mpu.enableCompassBypass();

    return initResult;
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

    gyroFiltered = Common::toVector3<float>(mpu.getNormalizedRotation());
}


void SimpleMPU6050Handler::config3AxisLPF(ThreeAxesLPF& lpf, float cutoffFreq)
{
    lpf.x.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.y.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.z.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
}
