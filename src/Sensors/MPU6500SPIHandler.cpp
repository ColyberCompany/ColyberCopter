/**
 * @file MPU6500SPIHandler.h
 * @author Jan Wielgus
 * @date 2022-04-08
 */

#include "MPU6500SPIHandler.h"

static const uint32_t SpiClock = 8000000l; // 8MHz clock (not tried 20MHz)


MPU6500SPIHandler::MPU6500SPIHandler(SPIClass& bus, uint8_t csPin):
    mpu(bus, SpiClock, csPin)
{
}


bool MPU6500SPIHandler::init_priv()
{
    if (Accelerometer::isInitialized() || Gyroscope::isInitialized())
        return true;

    if (!mpu.initialize())
        return false;

    mpu.setAccRange(MPU6500SPI::AccRange::Range_8G);
    mpu.setGyroScale(MPU6500SPI::GyroScale::Scale500DPS);

    return true;
}


void MPU6500SPIHandler::execute()
{
    mpu.readAll();
}
