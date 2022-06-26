/**
 * @file MPU6500SPIHandler.h
 * @author Jan Wielgus
 * @date 2022-04-08
 */

#ifndef MPU6500SPIHANDLER_h
#define MPU6500SPIHANDLER_h

#include "Base/Accelerometer.h"
#include "Base/Gyroscope.h"
#include "Base/TemperatureSensor.h"
#include <MPU6500SPI.h>
#include <IExecutable.h>
#include <SPI.h>
#include <MedianFilter.h>
#include <AverageFilter.h>
#include <config.h>


class MPU6500SPIHandler : public Accelerometer, public Gyroscope, public TemperatureSensor, public IExecutable
{
public:
    static constexpr uint16_t UpdateFrequency_Hz = 1000;

private:
    MPU6500SPI mpu;

    Common::vector3<FL::MedianFilter<float, 3>> accMedianFilter;
    Common::vector3Float accVal;

    static constexpr uint16_t GyroSamplesToAverage = UpdateFrequency_Hz / Config::MainFrequency_Hz;
    Common::vector3<FL::AverageFilter<float, GyroSamplesToAverage>> gyroAverageFilter;
    Common::vector3Float gyroVal;

public:
    MPU6500SPIHandler(SPIClass& bus, uint8_t csPin);

    const char* getName() override {
        return "mpu6500";
    }

float getTemperature_degC() override {
        return mpu.getTemperature_degC();
    }

private:
    bool init_priv() override;

    Common::vector3Float getAcc_norm_priv() override {
        return accVal;
    }

    Common::vector3Float getGyro_dps_priv() override {
        return gyroVal;
    }

    /**
     * @brief Reads new data from MPU6500.
     */
    void execute() override;
};


#endif
