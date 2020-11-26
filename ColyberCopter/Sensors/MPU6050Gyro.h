/**
 * @file MPU6050Acc.h
 * @author Jan Wielgus
 * @brief This class will take care of gyroscope calibration.
 * @date 2020-11-26
 * 
 */

#ifndef MPU6050GYRO_H
#define MPU6050GYRO_H

#include <IExecutable.h>
#include <SimpleMPU6050.h>
#include "Sensor.h"
#include "SensorsMediator.h"


class MPU6050Gyro: public IExecutable, public Sensor
{
private:
    SimpleMPU6050& mpu;

public:
    MPU6050Gyro(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050)
        : Sensor(sensorsMediator), mpu(mpu6050)
    {
    }

    // initialization is in adapter class
    bool initialize() override { return true; }

    // can't check here
    bool isGood() const override { return true; }


    void execute() override
    {
        // called periodically by MPU6050Adapter

        // run calibration process here
    }

    uint16_t startBackgroundCalibration(uint16_t amtOfSamples) override
    {
        // TODO: implement gyro calibration
    }

    FloatAxisVector getOffset() const override
    {
        // TODO: implement getOffset()
    }

    void setOffset(FloatAxisVector offset) override
    {
        // TODO: implement setOffset()
    }
    

    friend class MPU6050Adapter;
};


#endif

