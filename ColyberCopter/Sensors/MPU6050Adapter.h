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
        accClass(sensorsMediator, mpu),
        gyroClass(sensorsMediator, mpu)
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

    void execute() override
    {
        mpu.readRawData();

    }
};


#endif
