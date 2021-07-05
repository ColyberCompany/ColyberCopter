/**
 * @file TinyGPSAdapter.h
 * @author Antoni Wielgus
 * @brief Adapter for TinyGPS++.
 * @date 2021-07-05
 * 
 */


#ifndef TINYGPSADAPTER_H
#define TINYGPSADAPTER_H

#include "Sensor.h"
#include <IExecutable.h>
#include <TinyGPS++.h>


class TinyGPSAdapter: public Sensor, public IExecutable
{
    TinyGPSPlus gps;
    Stream& gpsSerial;

public:
    TinyGPSAdapter(SensorsMediator& SensorsMediator, Stream& gpsSerial);

    void execute() override;
    bool initialize() override;
    const char* getName() override;
};



#endif
