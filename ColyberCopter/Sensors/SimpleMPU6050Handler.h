/**
 * @file SimpleMPU6050Handler.h
 * @author Jan Wielgus
 * @brief Obtaining acc ang gyro radings using SimpleMPU6050 library.
 * @date 2021-08-12
 */

#ifndef MPU6050ADAPTER_H
#define MPU6050ADAPTER_H

#include "Base/Accelerometer.h"
#include "Base/Gyroscope.h"
#include "../Common/Vector3.h"
#include <SimpleMPU6050.h>
#include <LowPassFilter.h>
#include <IExecutable.h>


class SimpleMPU6050Handler : private SimpleMPU6050, public IExecutable
{
    typedef Common::vector3<LowPassFilter<float>> ThreeAxesLPF;
    ThreeAxesLPF accLPF; // accelerometer low-pass filter
    bool sensorInitialized_flag = false;

    Common::vector3Float accNormFiltered;
    Common::vector3Float gyroNormFiltered;


public:
    SimpleMPU6050Handler();

    bool initialize();
    Common::vector3Float getNormalizedAcceleration();
    Common::vector3Float getNormalizedRotation();

    using SimpleMPU6050::getAccOffset;
    using SimpleMPU6050::getGyroOffset;
    using SimpleMPU6050::setAccOffset;
    using SimpleMPU6050::setGyroOffset;
    using SimpleMPU6050::getTemperature;

private:
    /**
     * @brief Reads new data from MPU6050 and perform filtering.
     */
    void execute() override;

    /**
     * @brief Setup three low-pass filters.
     * @param lpf Vector of filters to setup.
     * @param cutoffFreq It's cutoff frequency.
     */
    void config3AxisLPF(ThreeAxesLPF& lpf, float cutoffFreq);
};



class MPU6050Acc: public Accelerometer
{
    SimpleMPU6050Handler& mpu;

public:
    MPU6050Acc(SimpleMPU6050Handler& simpleMPU6050Handler);
    bool initSensor() override;
    const char* getName() override;

    Common::vector3Float get_norm() override;
};



class MPU6050Gyro: public Gyroscope
{
    SimpleMPU6050Handler& mpu;

public:
    MPU6050Gyro(SimpleMPU6050Handler& simpleMPU6050Handler);
    bool initSensor() override;
    const char* getName() override;

    Common::vector3Float get_degPerSec() override;
};


#endif
