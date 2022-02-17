/**
 * @file SimpleMPU6050Handler.cpp
 * @author Jan Wielgus
 * @date 2021-08-12
 */

#include "Sensors/SimpleMPU6050Handler.h"
#include "config.h"


SimpleMPU6050Handler::SimpleMPU6050Handler()
{
}


bool SimpleMPU6050Handler::initSensor()
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


const char* SimpleMPU6050Handler::getName()
{
    return "mpu6050";
}


Common::vector3Float SimpleMPU6050Handler::get_norm()
{
    return accFiltered;
}


float SimpleMPU6050Handler::getX_norm()
{
    return accFiltered.x;
}


float SimpleMPU6050Handler::getY_norm()
{
    return accFiltered.y;
}


float SimpleMPU6050Handler::getZ_norm()
{
    return accFiltered.z;
}


Common::vector3Float SimpleMPU6050Handler::get_degPerSec()
{
    return gyroFiltered;
}


float SimpleMPU6050Handler::getX_degPerSec()
{
    return gyroFiltered.x;
}


float SimpleMPU6050Handler::getY_degPerSec()
{
    return gyroFiltered.y;
}


float SimpleMPU6050Handler::getZ_degPerSec()
{
    return gyroFiltered.z;
}


float SimpleMPU6050Handler::getTemperature_degC()
{
    return mpu.getTemperature();
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

    auto gyroNorm = mpu.getNormalizedRotation();
    gyroFiltered = Common::vector3Float(gyroNorm.x, gyroNorm.y, gyroNorm.z);
}


void SimpleMPU6050Handler::config3AxisLPF(ThreeAxesLPF& lpf, float cutoffFreq)
{
    lpf.x.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.y.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.z.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
}
