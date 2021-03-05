/**
 * @file HMC5883LAdapter.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-03-04
 * 
 */

#include "../Sensors/HMC5883LAdapter.h"


HMC5883LAdapter::HMC5883LAdapter(SensorsMediator& sensorsMediator, SimpleMPU6050* mpu6050)
    : Sensor(sensorsMediator)
{
    mpu = mpu6050;
}


bool HMC5883LAdapter::initialize()
{
    mpu->enableCompassBypass();

    int attempts = 0;
    do {
        initResultFlag = compass.initialize();
        attempts++;
    } while (initResultFlag == false && attempts < 3);

    return initResultFlag;
}


void HMC5883LAdapter::execute()
{
    compass.readRaw();

    calibrationLoop();

    SimpleHMC5883L::vector3Float norm = compass.getNormalized();
    sensorsMediator.updateMag(vector3Float(norm.x, norm.y, norm.z));
}


uint16_t HMC5883LAdapter::startBackgroundCalibration(uint16_t amtOfSamples)
{
    compass.setCompassOffset(0, 0, 0);

    const SimpleHMC5883L::vector3Int16& raw = compass.getRaw();
    mins.x = maxs.x = raw.x;
    mins.y = maxs.y = raw.y;
    mins.z = maxs.z = raw.z;

    calibCounter.reset(amtOfSamples);

    return getInterval_s() * amtOfSamples + 1;
}


FloatAxisVector HMC5883LAdapter::getOffset() const
{
    const SimpleHMC5883L::vector3Int16& magOffset = compass.getCompassOffset();
    return FloatAxisVector(3, magOffset.x, magOffset.y, magOffset.z);
}


void HMC5883LAdapter::setOffset(FloatAxisVector offset)
{
    using Enums::AxisType;
    compass.setCompassOffset(
        offset.getAxis(AxisType::AxisX),
        offset.getAxis(AxisType::AxisY),
        offset.getAxis(AxisType::AxisZ));
}


void HMC5883LAdapter::calibrationLoop()
{
    if (calibCounter.getCurrentCounter() > 0)
    {
        const SimpleHMC5883L::vector3Int16& raw = compass.getRaw();
        mins.x = min(raw.x, mins.x);
        mins.y = min(raw.y, mins.y);
        mins.z = min(raw.z, mins.z);

        maxs.x = max(raw.x, maxs.x);
        maxs.y = max(raw.y, maxs.y);
        maxs.z = max(raw.z, maxs.z);

        // if calibration ends now
        if (calibCounter.getCurrentCounter() == 1)
        {
            compass.setCompassOffset(
                (maxs.x + mins.x) / 2.f + 0.5f,
                (maxs.y + mins.y) / 2.f + 0.5f,
                (maxs.z + mins.z) / 2.f + 0.5f);
        }

        calibCounter.decrement();
    }
}
