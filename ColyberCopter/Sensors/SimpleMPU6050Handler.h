/**
 * @file SimpleMPU6050Handler.h
 * @author Jan Wielgus
 * @brief Obtaining acc ang gyro readings using SimpleMPU6050 library.
 * @date 2021-08-12
 */

#ifndef SIMPLEMPU6050HANDLER_H
#define SIMPLEMPU6050HANDLER_H

#include "Base/Accelerometer.h"
#include "Base/Gyroscope.h"
#include "Base/TemperatureSensor.h"
#include "../Common/Vector3.h"
#include <SimpleMPU6050.h>
#include <LowPassFilter.h>
#include <IExecutable.h>


class SimpleMPU6050Handler : public Accelerometer, public Gyroscope, public TemperatureSensor, public IExecutable
{
    SimpleMPU6050 mpu;
    Common::vector3Float accFiltered;
    Common::vector3Float gyroFiltered;

    typedef Common::vector3<LowPassFilter<float>> ThreeAxesLPF;
    ThreeAxesLPF accLPF; // accelerometer low-pass filter


public:
    SimpleMPU6050Handler();

private:
    bool initSensor() override;
    const char* getName() override;

    /**
     * @brief Accelerometer data.
     */
    Common::vector3Float get_norm() override;

    /**
     * @brief Gyroscope data.
     */
    Common::vector3Float get_degPerSec() override;

    float getTemperature_degC() override;

    /**
     * @brief Reads new data from MPU6050 and perform filtering.
     */
    void execute();

    /**
     * @brief Setup three low-pass filters.
     * @param lpf Vector of filters to setup.
     * @param cutoffFreq It's cutoff frequency.
     */
    void config3AxisLPF(ThreeAxesLPF& lpf, float cutoffFreq);
};


#endif
