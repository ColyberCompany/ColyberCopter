/**
 * @file TinyGPSAdapter.h
 * @author Antoni Wielgus
 * @date 2021-07-05
 */

#ifndef TINYGPSPLUSADAPTER_h
#define TINYGPSPLUSADAPTER_h

#include "Base/GPS.h"
#include <IExecutable.h>
#include <TinyGPSPlus.h>
#include <Arduino.h>


class TinyGPSPlusAdapter : public GPS, public IExecutable
{
    TinyGPSPlus gps;
    HardwareSerial& serial;

public:
    TinyGPSPlusAdapter(HardwareSerial& serial);

    bool init_priv() override;
    bool isOperating() const override;
    const char* getName() override;
    double getLatitude_deg() override;
    double getLongitude_deg() override;
    uint32_t getSattelitesAmt() override;
    float getSpeed_kmph() override;

private:
    void execute() override;
};


#endif
