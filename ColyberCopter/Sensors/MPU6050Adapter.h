/**
 * @file MPU6050Adapter.h
 * @author Jan Wielgus
 * @brief Adapter for MPU6050 accelerometer and gyro.
 * @date 2020-11-25
 * 
 */

#ifndef MPU6050ADAPTER_H
#define MPU6050ADAPTER_H

#include "Sensor.h"
#include "SensorsMediator.h"
#include "../Common/Counter.h"
#include "../config.h"
#include <Task.h>
#include <SimpleMPU6050.h>
#include <LowPassFilter.h>


class MPU6050Adapter;
class MPU6050Acc;
class MPU6050Gyro;




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
     * @param deltaTime Time between next checkCalibration() method calls [in seconds].
     */
    MPU6050Acc(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050, float deltaTime)
        : Sensor(sensorsMediator), mpu(mpu6050)
    {
        this->deltaTime = deltaTime;
    }

    MPU6050Acc(const MPU6050Acc&) = delete;
    MPU6050Acc& operator=(const MPU6050Acc&) = delete;

    // initialization is in adapter class
    bool initialize() override { return true; } // FIXME: try to return there real value


    /**
     * @brief Sensor have to be as horizontal as possible and don't move at all
     * during the calibration process.
     */
    void checkCalibration()
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
        const SimpleMPU6050::vector3Int16& accOffset = mpu.getAccOffset();
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





class MPU6050Gyro: public Sensor
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
     * @param deltaTime Time between next checkCalibration() method calls [in seconds].
     */
    MPU6050Gyro(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050, float deltaTime)
        : Sensor(sensorsMediator), mpu(mpu6050)
    {
        this->deltaTime = deltaTime;
    }

    MPU6050Gyro(const MPU6050Gyro&) = delete;
    MPU6050Gyro& operator=(const MPU6050Gyro&) = delete;

    // initialization is in adapter class
    bool initialize() override { return true; } // FIXME: try to return there real value


    /**
     * @brief Sensor have to don't move at all (can be in any position
     * but as steady as possible).
     */
    void checkCalibration()
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

    uint16_t startBackgroundCalibration(uint16_t amtOfSamples) override
    {
        mpu.setGyroOffset(0, 0, 0);

        sumX = 0;
        sumY = 0;
        sumZ = 0;

        calibCounter.reset(amtOfSamples);

        return deltaTime * amtOfSamples + 1;
    }

    FloatAxisVector getOffset() const override
    {
        const SimpleMPU6050::vector3Int16& gyroOffset = mpu.getGyroOffset();
        return FloatAxisVector(3, gyroOffset.x, gyroOffset.y, gyroOffset.z);
    }

    void setOffset(FloatAxisVector offset) override
    {
        using Enums::AxisType;
        mpu.setGyroOffset(
            offset.getAxis(AxisType::AxisX),
            offset.getAxis(AxisType::AxisY),
            offset.getAxis(AxisType::AxisZ));
    }
    

    friend class MPU6050Adapter;
};






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
