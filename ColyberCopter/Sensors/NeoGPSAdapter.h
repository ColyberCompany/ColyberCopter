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

// TODO: implementations in cpp file


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
};


#endif
