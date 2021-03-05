/**
 * @file MPU6050Adapter.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-03-04
 * 
 */

#include "../Sensors/MPU6050Adapter.h"
#include "../config.h"


MPU6050Adapter::AccCalib::AccCalib(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050)
    : Sensor(sensorsMediator), mpu(mpu6050)
{
}


bool MPU6050Adapter::AccCalib::initialize()
{
    return true; // FIXME: make that initialization is made here or in GyroCalib class (only once)
}


void MPU6050Adapter::AccCalib::calibrationLoop()
{
    // called periodically by MPU6050Adapter

    if (calibCounter.getCurrentCounter() > 0)
    {
        SimpleMPU6050::vector3Int16& accRaw = mpu.getRawAcceleration();

        calibSumVector.x += accRaw.x;
        calibSumVector.y += accRaw.y;
        calibSumVector.z += accRaw.z - mpu.getRawAccValueFor1G();

        // if calibration ends now
        if (calibCounter.getCurrentCounter() == 1)
        {
            uint16_t averagedSamples = calibCounter.getInitialCounter();
            mpu.setAccOffset(
                (double)calibSumVector.x / averagedSamples + 0.5f,
                (double)calibSumVector.y / averagedSamples + 0.5f,
                (double)calibSumVector.z / averagedSamples + 0.5f);
        }

        calibCounter.decrement();
    }
}


uint16_t MPU6050Adapter::AccCalib::startBackgroundCalibration(uint16_t amtOfSamples)
{
    mpu.setAccOffset(0, 0, 0);

    calibSumVector.x = 0;
    calibSumVector.y = 0;
    calibSumVector.z = 0;

    calibCounter.reset(amtOfSamples);

    return Config::MainInterval_s * amtOfSamples + 1;
}


FloatAxisVector MPU6050Adapter::AccCalib::getOffset() const
{
    const SimpleMPU6050::vector3Int16& accOffset = mpu.getAccOffset();
    return FloatAxisVector(3, accOffset.x, accOffset.y, accOffset.z);
}


void MPU6050Adapter::AccCalib::setOffset(FloatAxisVector offset)
{
    using Enums::AxisType;
    mpu.setAccOffset(
        offset.getAxis(AxisType::AxisX),
        offset.getAxis(AxisType::AxisY),
        offset.getAxis(AxisType::AxisZ));
}







MPU6050Adapter::GyroCalib::GyroCalib(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050)
    : Sensor(sensorsMediator), mpu(mpu6050)
{
}


bool MPU6050Adapter::GyroCalib::initialize()
{
    return true; // FIXME: make that initialization is made here or in GyroCalib class (only once)
}


void MPU6050Adapter::GyroCalib::calibrationLoop()
{
    // called periodically by MPU6050Adapter

    if (calibCounter.getCurrentCounter() > 0)
    {
        SimpleMPU6050::vector3Int16& gyroRaw = mpu.getRawRotation();

        calibSumVector.x += gyroRaw.x;
        calibSumVector.y += gyroRaw.y;
        calibSumVector.z += gyroRaw.z;

        // if calibration ends now
        if (calibCounter.getCurrentCounter() == 1)
        {
            uint16_t averagedSamples = calibCounter.getInitialCounter();
            mpu.setGyroOffset(
                (double)calibSumVector.x / averagedSamples + 0.5f,
                (double)calibSumVector.y / averagedSamples + 0.5f,
                (double)calibSumVector.z / averagedSamples + 0.5f);
        }

        calibCounter.decrement();
    }
}


uint16_t MPU6050Adapter::GyroCalib::startBackgroundCalibration(uint16_t amtOfSamples)
{
    mpu.setGyroOffset(0, 0, 0);

    calibSumVector.x = 0;
    calibSumVector.y = 0;
    calibSumVector.z = 0;

    calibCounter.reset(amtOfSamples);

    return Config::MainInterval_s * amtOfSamples + 1;
}


FloatAxisVector MPU6050Adapter::GyroCalib::getOffset() const
{
    const SimpleMPU6050::vector3Int16& gyroOffset = mpu.getGyroOffset();
    return FloatAxisVector(3, gyroOffset.x, gyroOffset.y, gyroOffset.z);
}


void MPU6050Adapter::GyroCalib::setOffset(FloatAxisVector offset)
{
    using Enums::AxisType;
    mpu.setGyroOffset(
        offset.getAxis(AxisType::AxisX),
        offset.getAxis(AxisType::AxisY),
        offset.getAxis(AxisType::AxisZ));
}








MPU6050Adapter::MPU6050Adapter(SensorsMediator& sensorsMediator)
    : accCalib(sensorsMediator, mpu),
    gyroCalib(sensorsMediator, mpu)
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

    accCalib.initResult = true;
    gyroCalib.initResult = true;

    return initResult;
}


bool MPU6050Adapter::isGood() const
{
    return initResult; // FIXME: this method should return true if acc and gyro classes return true (??)
}


void MPU6050Adapter::execute()
{
    mpu.readRawData();

    SimpleMPU6050::vector3Float& accNorm = mpu.getNormalizedAcceleration();
    //accCalib.sensorsMediator.updateAcc(vector3Float(accNorm.x, accNorm.y, accNorm.z));
    accCalib.sensorsMediator.updateAcc(vector3Float(
        accLPF.x.update(accNorm.x),
        accLPF.y.update(accNorm.y),
        accLPF.z.update(accNorm.z)
    ));

    SimpleMPU6050::vector3Float& gyroNorm = mpu.getNormalizedRotation();
    //gyroCalib.sensorsMediator.updateGyro(vector3Float(gyroNorm.x, gyroNorm.y, gyroNorm.z));
    gyroCalib.sensorsMediator.updateGyro(vector3Float(
        gyroLPF.x.update(gyroNorm.x),
        gyroLPF.y.update(gyroNorm.y),
        gyroLPF.z.update(gyroNorm.z)
    ));

    // You can update temperature there

    accCalib.calibrationLoop();
    gyroCalib.calibrationLoop();
}


Sensor* MPU6050Adapter::getAccSensor()
{
    return &accCalib;
}


Sensor* MPU6050Adapter::getGyroSensor()
{
    return &gyroCalib;
}


SimpleMPU6050* MPU6050Adapter::getMPU6050Ptr()
{
    return &mpu;
}


void MPU6050Adapter::config3AxisLPF(ThreeAxesLPF& lpf, float cutoffFreq)
{
    lpf.x.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.y.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.z.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
}
