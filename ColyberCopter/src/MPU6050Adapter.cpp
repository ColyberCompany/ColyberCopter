/**
 * @file MPU6050Adapter.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-03-04
 * 
 */

#include "../Sensors/MPU6050Adapter.h"


MPU6050Acc::MPU6050Acc(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050, float deltaTime)
    : Sensor(sensorsMediator), mpu(mpu6050)
{
    this->deltaTime = deltaTime;
}


bool MPU6050Acc::initialize()
{
    return true; // FIXME: try to return there real value
}


void MPU6050Acc::checkCalibration()
{
    // called periodically by MPU6050Adapter

    if (calibCounter.getCurrentCounter() > 0)
    {
        SimpleMPU6050::vector3Int16& accRaw = mpu.getRawAcceleration();

        sumX += accRaw.x;
        sumY += accRaw.y;
        sumZ += accRaw.z - mpu.getRawAccValueFor1G();

        // if calibration ends now
        if (calibCounter.getCurrentCounter() == 1)
        {
            uint16_t averagedSamples = calibCounter.getInitialCounter();
            mpu.setAccOffset(
                (double)sumX / averagedSamples + 0.5f,
                (double)sumY / averagedSamples + 0.5f,
                (double)sumZ / averagedSamples + 0.5f);
        }

        calibCounter.decrement();
    }
}


uint16_t MPU6050Acc::startBackgroundCalibration(uint16_t amtOfSamples)
{
    mpu.setAccOffset(0, 0, 0);

    sumX = 0;
    sumY = 0;
    sumZ = 0;

    calibCounter.reset(amtOfSamples);

    return deltaTime * amtOfSamples + 1;
}


FloatAxisVector MPU6050Acc::getOffset() const
{
    const SimpleMPU6050::vector3Int16& accOffset = mpu.getAccOffset();
    return FloatAxisVector(3, accOffset.x, accOffset.y, accOffset.z);
}


void MPU6050Acc::setOffset(FloatAxisVector offset)
{
    using Enums::AxisType;
    mpu.setAccOffset(
        offset.getAxis(AxisType::AxisX),
        offset.getAxis(AxisType::AxisY),
        offset.getAxis(AxisType::AxisZ));
}







MPU6050Gyro::MPU6050Gyro(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050, float deltaTime)
    : Sensor(sensorsMediator), mpu(mpu6050)
{
    this->deltaTime = deltaTime;
}


bool MPU6050Gyro::initialize()
{
    return true; // FIXME: try to return there real value
}


void MPU6050Gyro::checkCalibration()
{
    // called periodically by MPU6050Adapter

    if (calibCounter.getCurrentCounter() > 0)
    {
        SimpleMPU6050::vector3Int16& gyroRaw = mpu.getRawRotation();

        sumX += gyroRaw.x;
        sumY += gyroRaw.y;
        sumZ += gyroRaw.z;

        // if calibration ends now
        if (calibCounter.getCurrentCounter() == 1)
        {
            uint16_t averagedSamples = calibCounter.getInitialCounter();
            mpu.setGyroOffset(
                (double)sumX / averagedSamples + 0.5f,
                (double)sumY / averagedSamples + 0.5f,
                (double)sumZ / averagedSamples + 0.5f);
        }

        calibCounter.decrement();
    }
}


uint16_t MPU6050Gyro::startBackgroundCalibration(uint16_t amtOfSamples)
{
    mpu.setGyroOffset(0, 0, 0);

    sumX = 0;
    sumY = 0;
    sumZ = 0;

    calibCounter.reset(amtOfSamples);

    return deltaTime * amtOfSamples + 1;
}


FloatAxisVector MPU6050Gyro::getOffset() const
{
    const SimpleMPU6050::vector3Int16& gyroOffset = mpu.getGyroOffset();
    return FloatAxisVector(3, gyroOffset.x, gyroOffset.y, gyroOffset.z);
}


void MPU6050Gyro::setOffset(FloatAxisVector offset)
{
    using Enums::AxisType;
    mpu.setGyroOffset(
        offset.getAxis(AxisType::AxisX),
        offset.getAxis(AxisType::AxisY),
        offset.getAxis(AxisType::AxisZ));
}








MPU6050Adapter::MPU6050Adapter(SensorsMediator& sensorsMediator)
    : accClass(sensorsMediator, mpu, getInterval_s()),
    gyroClass(sensorsMediator, mpu, getInterval_s())
{
}


bool MPU6050Adapter::initialize()
{
    int attempts = 0;
    do {
        initResult = mpu.initialize();
        attempts++;
    } while (initResult == false && attempts < 3);

    config3AxisLPF(accLPF, Config::AccLPFCutOffFreq);
    config3AxisLPF(gyroLPF, Config::GyroLPFCutOffFreq);

    accClass.initResult = true;
    gyroClass.initResult = true;

    return initResult;
}


bool MPU6050Adapter::isGood() const
{
    return initResult;
}


void MPU6050Adapter::execute()
{
    mpu.readRawData();

    SimpleMPU6050::vector3Float& accNorm = mpu.getNormalizedAcceleration();
    //accClass.sensorsMediator.updateAcc(vector3Float(accNorm.x, accNorm.y, accNorm.z));
    accClass.sensorsMediator.updateAcc(vector3Float(
        accLPF.x.update(accNorm.x),
        accLPF.y.update(accNorm.y),
        accLPF.z.update(accNorm.z)
    ));

    SimpleMPU6050::vector3Float& gyroNorm = mpu.getNormalizedRotation();
    //gyroClass.sensorsMediator.updateGyro(vector3Float(gyroNorm.x, gyroNorm.y, gyroNorm.z));
    gyroClass.sensorsMediator.updateGyro(vector3Float(
        gyroLPF.x.update(gyroNorm.x),
        gyroLPF.y.update(gyroNorm.y),
        gyroLPF.z.update(gyroNorm.z)
    ));

    // You can update temperature there

    accClass.checkCalibration();
    gyroClass.checkCalibration();
}


Sensor* MPU6050Adapter::getAccSensor()
{
    return &accClass;
}


Sensor* MPU6050Adapter::getGyroSensor()
{
    return &gyroClass;
}


SimpleMPU6050* MPU6050Adapter::getMPU6050Ptr()
{
    return &mpu;
}


void MPU6050Adapter::config3AxisLPF(ThreeAxisLPF& lpf, float cutoffFreq)
{
    lpf.x.reconfigureFilter(cutoffFreq, getInterval_s());
    lpf.y.reconfigureFilter(cutoffFreq, getInterval_s());
    lpf.z.reconfigureFilter(cutoffFreq, getInterval_s());
}
