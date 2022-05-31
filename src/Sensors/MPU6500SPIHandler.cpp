/**
 * @file MPU6500SPIHandler.h
 * @author Jan Wielgus
 * @date 2022-04-08
 */

#include "MPU6500SPIHandler.h"
#include "config.h"

static const uint32_t SpiClock = 8000000l; // 8MHz clock (not tried 20MHz)
constexpr float AccLPFCutOffFreq = 8.f;

// TODO: figure out place for calibration values (for specific hardware)
const FusionMatrix accMisalignment = {0.997712, -0.003394, 0.001708, -0.003394, 0.996472, 0.000751, 0.001708, 0.000751, 0.984676};
const FusionVector accSensitivity = {1.0f, 1.0f, 1.0f};
const FusionVector accOffset = {0.013689, 0.009321, -0.102916};
const FusionMatrix gyroMisalignment = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
const FusionVector gyroSensitivity = {1.0f, 1.0f, 1.0f};
const FusionVector gyroOffset = {0.0f, 0.0f, 0.0f};


MPU6500SPIHandler::MPU6500SPIHandler(SPIClass& bus, uint8_t csPin):
    mpu(bus, SpiClock, csPin),
    accLPF(
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

    auto acc = mpu.getNormalizedAcceleration();
    accFiltered = Common::vector3Float(
        accLPF.x.update(acc.x),
        accLPF.y.update(acc.y),
        accLPF.z.update(acc.z)
    );
}
