/**
 * @file TinyGPSPlusAdapter.cpp
 * @author Antoni Wielgus
 * @date 2022-07-05
 */

#include "TinyGPSPlusAdapter.h"


TinyGPSPlusAdapter::TinyGPSPlusAdapter(HardwareSerial& serial)
    : serial(serial)
{
}


bool TinyGPSPlusAdapter::init_priv()
{
    serial.begin(9600);
    return true;
}


bool TinyGPSPlusAdapter::isOperating() const
{
    uint32_t satelitesAmt = const_cast<TinyGPSPlusAdapter*>(this)->gps.satellites.value();
    return (gps.location.isValid() && satelitesAmt >= 3);
}


const char* TinyGPSPlusAdapter::getName()
{
    return "tinyGPS++";
}


double TinyGPSPlusAdapter::getLatitude_deg()
{
    return gps.location.lat();
}


double TinyGPSPlusAdapter::getLongitude_deg()
{
    return gps.location.lng();
}


uint32_t TinyGPSPlusAdapter::getSattelitesAmt()
{
    return gps.satellites.value();
}


float TinyGPSPlusAdapter::getSpeed_kmph()
{
    return gps.speed.kmph();
}


void TinyGPSPlusAdapter::execute()
{
    while (serial.available())
    {
        gps.encode(serial.read());
    }
}


