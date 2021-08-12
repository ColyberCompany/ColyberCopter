/**
 * @file SimpleMPU6050Handler.cpp
 * @author Jan Wielgus
 * @date 2021-08-12
 */

#include "../Sensors/SimpleMPU6050Handler.h"
#include "../config.h"


SimpleMPU6050Handler::SimpleMPU6050Handler()
{
}


bool SimpleMPU6050Handler::initialize()
{
    if (sensorInitialized_flag)
        return true;

    sensorInitialized_flag = SimpleMPU6050::initialize();
    config3AxisLPF(accLPF, Config::AccLPFCutOffFreq);

    return sensorInitialized_flag;
}


Common::vector3Float SimpleMPU6050Handler::getNormalizedAcceleration()
{
    return accNormFiltered;
}


Common::vector3Float SimpleMPU6050Handler::getNormalizedRotation()
{
    return gyroNormFiltered;
}


void SimpleMPU6050Handler::execute()
{
    SimpleMPU6050::readRawData();

    auto accNorm = SimpleMPU6050::getNormalizedAcceleration();
    // accNormFiltered = Common::vector3Float(accNorm.x, accNorm.y, accNorm.z); // version without lpf filter
    accNormFiltered = Common::vector3Float(
        accLPF.x.update(accNorm.x),
        accLPF.y.update(accNorm.y),
        accLPF.z.update(accNorm.z)
    );

    auto gyroNorm = SimpleMPU6050::getNormalizedRotation();
    gyroNormFiltered = Common::vector3Float(gyroNorm.x, gyroNorm.y, gyroNorm.z);
}


void SimpleMPU6050Handler::config3AxisLPF(ThreeAxesLPF& lpf, float cutoffFreq)
{
    lpf.x.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.y.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.z.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
}


MPU6050Acc::MPU6050Acc(SimpleMPU6050Handler& simpleMPU6050Handler)
    : Accelerometer(Enums::SensorTypes::ACCELEROMETER),
      mpu(simpleMPU6050Handler)
{
}


bool MPU6050Acc::initSensor()
{
    using Config::AccOffset;

    bool result = mpu.initialize();
    mpu.setAccOffset(AccOffset.x, AccOffset.y, AccOffset.z);

    return result;
}


const char* MPU6050Acc::getName()
{
    return "mpu6050 acc";
}


Common::vector3Float MPU6050Acc::get_norm()
{
    return mpu.getNormalizedAcceleration();
}


MPU6050Gyro::MPU6050Gyro(SimpleMPU6050Handler& simpleMPU6050Handler)
    : Gyroscope(Enums::SensorTypes::GYROSCOPE),
      mpu(simpleMPU6050Handler)
{
}


bool MPU6050Gyro::initSensor()
{
    using Config::GyroOffset;

    bool result = mpu.initialize();
    mpu.setGyroOffset(GyroOffset.x, GyroOffset.y, GyroOffset.z);

    return result;
}


const char* MPU6050Gyro::getName()
{
    return "mpu6050 gyro";
}


Common::vector3Float MPU6050Gyro::get_degPerSec()
{
    return mpu.getNormalizedRotation();
}
