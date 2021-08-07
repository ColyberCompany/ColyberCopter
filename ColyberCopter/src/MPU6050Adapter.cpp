/**
 * @file MPU6050Adapter.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-03-04
 * 
 */

#include "../Sensors/MPU6050Adapter.h"
#include "../config.h"

using Common::vector3Float;
using Common::FloatAxisVector;


MPU6050Adapter::AccCalib::AccCalib(SensorsMediator& sensorsMediator, MPU6050Adapter& _mpuAdapter)
    : Sensor(Enums::SensorTypes::ACCELEROMETER, sensorsMediator),
      mpuAdapter(_mpuAdapter)
{
    using Config::AccOffset;
    setOffset(FloatAxisVector(AccOffset.x, AccOffset.y, AccOffset.z));
}


bool MPU6050Adapter::AccCalib::initialize()
{
    mpuAdapter.initializeMPU6050IfWasNotInitialized();
    return isGood();
}


void MPU6050Adapter::AccCalib::calibrationLoop()
{
    // called periodically by MPU6050Adapter

    if (calibCounter.getCurrentCounter() > 0)
    {
        SimpleMPU6050::vector3Int16& accRaw = mpuAdapter.mpu.getRawAcceleration();

        calibSumVector.x += accRaw.x;
        calibSumVector.y += accRaw.y;
        calibSumVector.z += accRaw.z - mpuAdapter.mpu.getRawAccValueFor1G();

        // if calibration ends now
        if (calibCounter.getCurrentCounter() == 1)
        {
            uint16_t averagedSamples = calibCounter.getInitialCounter();
            mpuAdapter.mpu.setAccOffset(
                (double)calibSumVector.x / averagedSamples + 0.5f,
                (double)calibSumVector.y / averagedSamples + 0.5f,
                (double)calibSumVector.z / averagedSamples + 0.5f);
        }

        calibCounter.decrement();
    }
}


uint16_t MPU6050Adapter::AccCalib::startBackgroundCalibration(uint16_t amtOfSamples)
{
    mpuAdapter.mpu.setAccOffset(0, 0, 0);

    calibSumVector.x = 0;
    calibSumVector.y = 0;
    calibSumVector.z = 0;

    calibCounter.reset(amtOfSamples);

    return Config::MainInterval_s * amtOfSamples + 1;
}


FloatAxisVector MPU6050Adapter::AccCalib::getOffset() const
{
    const SimpleMPU6050::vector3Int16& accOffset = mpuAdapter.mpu.getAccOffset();
    return FloatAxisVector(accOffset.x, accOffset.y, accOffset.z);
}


void MPU6050Adapter::AccCalib::setOffset(FloatAxisVector offset)
{
    using Enums::AxisType;
    mpuAdapter.mpu.setAccOffset(
        offset.getAxis(AxisType::AxisX),
        offset.getAxis(AxisType::AxisY),
        offset.getAxis(AxisType::AxisZ));
}


const char* MPU6050Adapter::AccCalib::getName()
{
    return "accelerometer";
}







MPU6050Adapter::GyroCalib::GyroCalib(SensorsMediator& sensorsMediator, MPU6050Adapter& _mpuAdapter)
    : Sensor(Enums::SensorTypes::GYROSCOPE, sensorsMediator),
      mpuAdapter(_mpuAdapter)
{
    using Config::GyroOffset;
    setOffset(FloatAxisVector(GyroOffset.x, GyroOffset.y, GyroOffset.z));
}


bool MPU6050Adapter::GyroCalib::initialize()
{
    mpuAdapter.initializeMPU6050IfWasNotInitialized();
    return isGood();
}


void MPU6050Adapter::GyroCalib::calibrationLoop()
{
    // called periodically by MPU6050Adapter

    if (calibCounter.getCurrentCounter() > 0)
    {
        SimpleMPU6050::vector3Int16& gyroRaw = mpuAdapter.mpu.getRawRotation();

        calibSumVector.x += gyroRaw.x;
        calibSumVector.y += gyroRaw.y;
        calibSumVector.z += gyroRaw.z;

        // if calibration ends now
        if (calibCounter.getCurrentCounter() == 1)
        {
            uint16_t averagedSamples = calibCounter.getInitialCounter();
            mpuAdapter.mpu.setGyroOffset(
                (double)calibSumVector.x / averagedSamples + 0.5f,
                (double)calibSumVector.y / averagedSamples + 0.5f,
                (double)calibSumVector.z / averagedSamples + 0.5f);
        }

        calibCounter.decrement();
    }
}


uint16_t MPU6050Adapter::GyroCalib::startBackgroundCalibration(uint16_t amtOfSamples)
{
    mpuAdapter.mpu.setGyroOffset(0, 0, 0);

    calibSumVector.x = 0;
    calibSumVector.y = 0;
    calibSumVector.z = 0;

    calibCounter.reset(amtOfSamples);

    return Config::MainInterval_s * amtOfSamples + 1;
}


FloatAxisVector MPU6050Adapter::GyroCalib::getOffset() const
{
    const SimpleMPU6050::vector3Int16& gyroOffset = mpuAdapter.mpu.getGyroOffset();
    return FloatAxisVector(gyroOffset.x, gyroOffset.y, gyroOffset.z);
}


void MPU6050Adapter::GyroCalib::setOffset(FloatAxisVector offset)
{
    using Enums::AxisType;
    mpuAdapter.mpu.setGyroOffset(
        offset.getAxis(AxisType::AxisX),
        offset.getAxis(AxisType::AxisY),
        offset.getAxis(AxisType::AxisZ));
}


const char* MPU6050Adapter::GyroCalib::getName()
{
    return "gyroscope";
}








MPU6050Adapter::MPU6050Adapter(SensorsMediator& sensorsMediator)
    : accCalib(sensorsMediator, *this),
    gyroCalib(sensorsMediator, *this)
{
}


void MPU6050Adapter::execute()
{
    mpu.readRawData();

    SimpleMPU6050::vector3Float& accNorm = mpu.getNormalizedAcceleration();
    //accCalib.sensorsMediator.updateAcc(vector3Float(accNorm.x, accNorm.y, accNorm.z)); // without filter
    accCalib.sensorsMediator.updateAcc(vector3Float(
        accLPF.x.update(accNorm.x),
        accLPF.y.update(accNorm.y),
        accLPF.z.update(accNorm.z)
    ));

    SimpleMPU6050::vector3Float& gyroNorm = mpu.getNormalizedRotation();
    //gyroCalib.sensorsMediator.updateGyro(vector3Float(gyroNorm.x, gyroNorm.y, gyroNorm.z)); // without filter
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


void MPU6050Adapter::initializeMPU6050IfWasNotInitialized()
{
    static bool haveBeenInitializedFlag = false;

    if (haveBeenInitializedFlag)
        return;

    bool initResultFlag = false;
    int attempts = 0;
    do {
        initResultFlag = mpu.initialize();
        attempts++;
    } while (initResultFlag == false && attempts < 3);

    if (initResultFlag == false)
        return;


    haveBeenInitializedFlag = true;

    // Update init flags in sensor classes for acc and gyro
    accCalib.initResultFlag = true;
    gyroCalib.initResultFlag = true;

    // Configure filters
    config3AxisLPF(accLPF, Config::AccLPFCutOffFreq);
    config3AxisLPF(gyroLPF, Config::GyroLPFCutOffFreq);
}


void MPU6050Adapter::config3AxisLPF(ThreeAxesLPF& lpf, float cutoffFreq)
{
    lpf.x.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.y.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
    lpf.z.reconfigureFilter(cutoffFreq, Config::MainInterval_s);
}
