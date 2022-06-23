/**
 * @file MPU6500SPIHandler.h
 * @author Jan Wielgus
 * @date 2022-04-08
 */

#include "MPU6500SPIHandler.h"
#include "config.h"

static const uint32_t SpiClock = 8000000l; // 8MHz clock (not tried 20MHz)
constexpr float AccLPFCutOffFreq = 15.f;

// TODO: figure out place for calibration values (for specific hardware)
const FusionMatrix accMisalignment = {0.997712f, -0.003394f, 0.001708f, -0.003394f, 0.996472f, 0.000751f, 0.001708f, 0.000751f, 0.984676f};
const FusionVector accSensitivity = {1.0f, 1.0f, 1.0f};
const FusionVector accOffset = {0.013689f, 0.009321f, -0.102916f};
const FusionMatrix gyroMisalignment = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
const FusionVector gyroSensitivity = {1.0f, 1.0f, 1.0f};
const FusionVector gyroOffset = {-0.9055204f, 0.9203771f, -0.0984093f};


MPU6500SPIHandler::MPU6500SPIHandler(SPIClass& bus, uint8_t csPin):
    mpu(bus, SpiClock, csPin),
    accLowPassFilter(
        {AccLPFCutOffFreq, Config::MainInterval_s},
        {AccLPFCutOffFreq, Config::MainInterval_s},
        {AccLPFCutOffFreq, Config::MainInterval_s}
    )
{
    accelerometer().setCalibration(CalibrationIntertial::Calibration {
        .misalignment = accMisalignment,
        .sensitivity = accSensitivity,
        .offset = accOffset
    });
    gyroscope().setCalibration(CalibrationIntertial::Calibration {
        .misalignment = gyroMisalignment,
        .sensitivity = gyroSensitivity,
        .offset = gyroOffset
    });
}


bool MPU6500SPIHandler::init_priv()
{
    if (Accelerometer::isInitialized() || Gyroscope::isInitialized())
        return true;

    if (!mpu.initialize())
        return false;

    mpu.setAccRange(MPU6500SPI::AccRange::Range_4G);
    mpu.setGyroScale(MPU6500SPI::GyroScale::Scale500DPS);

    return true;
}


void MPU6500SPIHandler::execute()
{
    mpu.readAll();
    accVal = Common::vector3Float(mpu.getNormalizedAcceleration());
    
    // Apply Median Filter
    accVal = Common::vector3Float(
        accMedianFilter.x.update(accVal.x),
        accMedianFilter.y.update(accVal.y),
        accMedianFilter.z.update(accVal.z)
    );
    // Apply Low-pass Filter
    accVal = Common::vector3Float(
        accLowPassFilter.x.update(accVal.x),
        accLowPassFilter.y.update(accVal.y),
        accLowPassFilter.z.update(accVal.z)
    );
}
