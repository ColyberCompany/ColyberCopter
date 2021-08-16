/**
 * @file TinyGPSAdapter.h
 * @author Antoni Wielgus
 * @brief Adapter for TinyGPS++.
 * @date 2021-07-05
 * 
 */


#ifndef TINYGPSADAPTER_H
#define TINYGPSADAPTER_H

#include "Base/GPS.h"
#include <IExecutable.h>
#include <TinyGPS++.h>


class TinyGPSAdapter: public GPS, public IExecutable
{
    TinyGPSPlus gps;
    Stream& gpsSerial;

public:
    TinyGPSAdapter(Stream& gpsSerial);

    bool initSensor() override;
    bool isOperating() const override;
    const char* getName() override;
    double getLatitude_deg() override;
    double getLongitude_deg() override;
    uint8_t getSattelitesAmt() override;
    float getSpeed_kmph() override;

private:
    void execute() override;
};


#endif
