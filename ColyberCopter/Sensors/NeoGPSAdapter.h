/**
 * @file NeoGPSAdapter.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Adapter for NeoGPS library.
 * @date 2021-03-03
 * 
 */

#ifndef NEOGPSADAPTER_H
#define NEOGPSADAPTER_H

#include "Sensor.h"
#include <NMEAGPS.h>
#include <Task.h>


class NeoGPSAdapter : public Sensor, public Task
{
    // TODO: private instances


public:
    NeoGPSAdapter(SensorsMediator& sensorsMediator)
        : Sensor(sensorsMediator)
    {
    }

    bool initialize() override
    {
        // TODO: initialize
    }

    void execute() override
    {
        // TODO: execute
    }

    uint16_t startBackgroundCalibration(uint16_t) override { return 0; }
    FloatAxisVector getOffset() const override { return FloatAxisVector(0); }
    void setOffset(FloatAxisVector offset) override {}
};


#endif
