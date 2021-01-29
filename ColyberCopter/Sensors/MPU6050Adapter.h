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
#include <LowPassFilter.h>
#include "../config.h"


class MPU6050Adapter: public Task
{
private:
    SimpleMPU6050 mpu;
    bool initResult = false;

    MPU6050Acc accClass;
    MPU6050Gyro gyroClass;

    // Low pass filters
    struct ThreeAxisLPF
    {
        LowPassFilter<float> x;
        LowPassFilter<float> y;
        LowPassFilter<float> z;
    };
    ThreeAxisLPF accLPF;
    ThreeAxisLPF gyroLPF;


public:
    MPU6050Adapter(SensorsMediator& sensorsMediator)
        : accClass(sensorsMediator, mpu, getInterval_s()),
        gyroClass(sensorsMediator, mpu, getInterval_s())
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

        config3AxisLPF(accLPF, Config::AccLPFCutOffFreq);
        config3AxisLPF(gyroLPF, Config::GyroLPFCutOffFreq);

        accClass.initResult = true;
        gyroClass.initResult = true;

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


private:
    /**
     * @brief Sets parameters for the three axis
     * LowPass filter (the same for all three).
     * @param lpf Three filters struct.
     * @param cutoffFreq Cut-off frequency.
     */
    void config3AxisLPF(ThreeAxisLPF& lpf, float cutoffFreq)
    {
        lpf.x.reconfigureFilter(cutoffFreq, getInterval_s());
        lpf.y.reconfigureFilter(cutoffFreq, getInterval_s());
        lpf.z.reconfigureFilter(cutoffFreq, getInterval_s());
    }
};


#endif
