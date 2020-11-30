/**
 * @file MPU6050Adapter.h
 * @author Jan Wielgus
 * @brief Adapter for MPU6050 accelerometer and gyro.
 * @date 2020-11-25
 * 
 */

#ifndef MPU6050ADAPTER_H
#define MPU6050ADAPTER_H

#include <SimpleMPU6050.h>
#include "Sensor.h"
#include "SensorsMediator.h"
#include <Task.h>
#include "MPU6050Acc.h"
#include "MPU6050Gyro.h"


class MPU6050Adapter: public Task
{
private:
    SimpleMPU6050 mpu;
    bool initResult = false;

    MPU6050Acc accClass;
    MPU6050Gyro gyroClass;


public:
    MPU6050Adapter(SensorsMediator& sensorsMediator)
        : accClass(sensorsMediator, mpu, interval / 1000000.f),
        gyroClass(sensorsMediator, mpu, interval / 1000000.f)
    {
    }

    // Call Wire.begin() before!
    bool initialize()
    {
        int attempts = 0;
        do {
            initResult = mpu.initialize();
            attempts++;
        } while (initResult == false && attempts < 3);

        return initResult;
    }

    bool isGood() const
    {
        return initResult;
    }

    void execute() override
    {
        mpu.readRawData();

        SimpleMPU6050::vector3Float& accNorm = mpu.getNormalizedAcceleration();
        accClass.sensorsMediator.updateAcc(vector3Float(accNorm.x, accNorm.y, accNorm.z));

        SimpleMPU6050::vector3Float& gyroNorm = mpu.getNormalizedRotation();
        gyroClass.sensorsMediator.updateGyro(vector3Float(gyroNorm.x, gyroNorm.y, gyroNorm.z));

        // You can update temperature there

        accClass.executeCalibration();
        gyroClass.executeCalibration();
    }

    Sensor* getAccSensor()
    {
        return &accClass;
    }

    Sensor* getGyroSensor()
    {
        return &gyroClass;
    }

    SimpleMPU6050* getMPU6050Ptr()
    {
        return &mpu;
    }
};


#endif
