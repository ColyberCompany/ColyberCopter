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


class HMC5883LAdapter: public Sensor, public Task
{
private:
    SimpleHMC5883L compass;
    FloatAxisVector offset;

public:
    HMC5883LAdapter(SensorsMediator& sensorsMediator)
        : Sensor(sensorsMediator), offset(3)
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
        // TODO: implement main action of compass and update values in sensors mediator
    }

    uint16_t startBackgroundCalibration(int16_t samplesToAverage) override
    {
        // TODO: compass calibration
    }

    FloatAxisVector getOffset() const override
    {
        return offset;
    }

    void setOffset(FloatAxisVector offset) override
    {
        this->offset = offset;
    }
};


#endif

