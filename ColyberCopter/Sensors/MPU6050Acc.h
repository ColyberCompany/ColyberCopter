/**
 * @file MPU6050Acc.h
 * @author Jan Wielgus
 * @brief This class will take care of accelerometer calibration.
 * @date 2020-11-26
 * 
 */

#ifndef MPU6050ACC_H
#define MPU6050ACC_H

#include <SimpleMPU6050.h>
#include "Sensor.h"
#include "SensorsMediator.h"
#include "Common/Counter.h"


class MPU6050Acc: public Sensor
{
private:
    SimpleMPU6050& mpu;

    int32_t sumX; // TODO: think how to make that this variables don't occupy memory all the time (they are needed for a short period or never)
    int32_t sumY; // Maybe something wih that, that probably always only one sensor will be calibrated at once (also all sensors are calibrated in the simmilar way).
    int32_t sumZ;
    Counter calibCounter;
    float deltaTime; // in seconds

public:
    /**
     * @param sensorsMediator Reference to the sensorsMediator.
     * @param mpu6050 Reference to the mpu6050 instance.
     * @param deltaTime Time between next executeCalibration() method calls [in seconds].
     */
    MPU6050Acc(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050, float deltaTime)
        : Sensor(sensorsMediator), mpu(mpu6050)
    {
        this->deltaTime = deltaTime;
    }

    MPU6050Acc(const MPU6050Acc&) = delete;
    MPU6050Acc& operator=(const MPU6050Acc&) = delete;

    // initialization is in adapter class
    bool initialize() override { return true; }

    // can't check here
    bool isGood() const override { return true; }


    /**
     * @brief Sensor have to be as horizontal as possible and don't move at all
     * during the calibration process.
     */
    void executeCalibration()
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

    uint16_t startBackgroundCalibration(uint16_t amtOfSamples) override
    {
        mpu.setAccOffset(0, 0, 0);

        sumX = 0;
        sumY = 0;
        sumZ = 0;

        calibCounter.reset(amtOfSamples);

        return deltaTime * amtOfSamples + 1;
    }

    FloatAxisVector getOffset() const override
    {
        SimpleMPU6050::vector3Int16& accOffset = mpu.getAccOffset();
        return FloatAxisVector(3, accOffset.x, accOffset.y, accOffset.z);
    }

    void setOffset(FloatAxisVector offset) override
    {
        using Enums::AxisType;
        mpu.setAccOffset(
            offset.getAxis(AxisType::AxisX),
            offset.getAxis(AxisType::AxisY),
            offset.getAxis(AxisType::AxisZ));
    }


    friend class MPU6050Adapter;
};


#endif

