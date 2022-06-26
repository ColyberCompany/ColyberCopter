/**
 * @file MPU6500SPIHandler.h
 * @author Jan Wielgus
 * @date 2022-04-08
 */

#include "MPU6500SPIHandler.h"
#include "config.h"
#include <MPU6050SPIRegisters.h>

static const uint32_t SpiClock = 8000000l; // 8MHz clock (not tried 20MHz)

// TODO: figure out place for calibration values (for specific hardware)
const FusionMatrix accMisalignment = {0.997712f, -0.003394f, 0.001708f, -0.003394f, 0.996472f, 0.000751f, 0.001708f, 0.000751f, 0.984676f};
const FusionVector accSensitivity = {1.0f, 1.0f, 1.0f};
const FusionVector accOffset = {0.013689f, 0.009321f, -0.102916f};
const FusionMatrix gyroMisalignment = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
const FusionVector gyroSensitivity = {1.0f, 1.0f, 1.0f};
const FusionVector gyroOffset = {-0.9055204f, 0.9203771f, -0.0984093f};


MPU6500SPIHandler::MPU6500SPIHandler(SPIClass& bus, uint8_t csPin):
    mpu(bus, SpiClock, csPin)
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

    // Custom configuration not provided by library (check MPU6500 register map)
    uint8_t tempReg;
    mpu.writeReg(MPUREG_SMPLRT_DIV, 0x00); // disable sample rate divider
    tempReg = mpu.readReg(MPUREG_GYRO_CONFIG);
    mpu.writeReg(MPUREG_GYRO_CONFIG, tempReg | B00); // Set FCHOICE_B to 00
    mpu.writeReg(MPUREG_CONFIG, B001); // Set DLPF_CFG to 001 (gyro low-pass filter, bandwidth 184Hz)
    mpu.writeReg(MPUREG_ACCEL_CONFIG_2, B0100); // Set ACCEL_FCHOICE_B and A_DLPF_CFG (accel low-pass filter, bandwidth 20Hz)

    return true;
}


void MPU6500SPIHandler::execute()
{
    mpu.readAll();

    gyroVal = Common::vector3Float(mpu.getNormalizedRotation());
    // Apply gyro Average filter
    gyroVal.x = gyroAverageFilter.x.update(gyroVal.x);
    gyroVal.y = gyroAverageFilter.y.update(gyroVal.y);
    gyroVal.z = gyroAverageFilter.z.update(gyroVal.z);

    accVal = Common::vector3Float(mpu.getNormalizedAcceleration());
    // Apply acc Median Filter
    accVal.x = accMedianFilter.x.update(accVal.x);
    accVal.y = accMedianFilter.y.update(accVal.y);
    accVal.z = accMedianFilter.z.update(accVal.z);
}
