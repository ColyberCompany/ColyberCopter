/**
 * @file HMC5883LAdapter.h
 * @author Jan Wielgus
 * @brief Adapter for HMC5883L magnetometer.
 * @date 2020-11-26
 * 
 */

#ifndef HMC5883LADAPTER_H
#define HMC5883LADAPTER_H

#include "Sensor.h"
#include <SimpleHMC5883L.h>
#include "SensorsMediator.h"
#include <Task.h>
#include "Common/Vector3.h"
#include "Common/Counter.h"


class HMC5883LAdapter: public Sensor, public Task
{
private:
    SimpleHMC5883L compass;

    // calibration
    SimpleHMC5883L::vector3Int16 mins;
    SimpleHMC5883L::vector3Int16 maxs;
    Counter calibCounter;


public:
    HMC5883LAdapter(SensorsMediator& sensorsMediator)
        : Sensor(sensorsMediator)
    {
    }

    bool initialize() override
    {
        int attempts = 0;
        do {
            initResult = compass.initialize();
            attempts++;
        } while (initResult == false && attempts < 3);

        return initResult;
    }

    void execute() override
    {
        compass.readRaw();

        checkCalibration();

        SimpleHMC5883L::vector3Float norm = compass.getNormalized();
        sensorsMediator.updateMag(vector3Float(norm.x, norm.y, norm.z));
    }

    uint16_t startBackgroundCalibration(uint16_t samplesToAverage) override
    {
        compass.setCompassOffset(0, 0, 0);

        const SimpleHMC5883L::vector3Int16& raw = compass.getRaw();
        mins.x = maxs.x = raw.x;
        mins.y = maxs.y = raw.y;
        mins.z = maxs.z = raw.z;

        calibCounter.reset(samplesToAverage);

        return (interval / 1000000.f) * samplesToAverage + 1;
    }

    FloatAxisVector getOffset() const override
    {
        SimpleHMC5883L::vector3Int16& magOffset = compass.getCompassOffset();
        return FloatAxisVector(3, magOffset.x, magOffset.y, magOffset.z);
    }

    void setOffset(FloatAxisVector offset) override
    {
        using Enums::AxisType;
        compass.setCompassOffset(
            offset.getAxis(AxisType::AxisX),
            offset.getAxis(AxisType::AxisY),
            offset.getAxis(AxisType::AxisZ));
    }



private:
    void checkCalibration()
    {
        if (calibCounter.getCurrentCounter() > 0)
        {
            SimpleHMC5883L::vector3Int16 raw = compass.getRaw();
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

};


#endif

