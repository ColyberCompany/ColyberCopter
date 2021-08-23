/**
 * @file TinyGPSAdapter.h
 * @author Antoni Wielgus
 * @date 2021-07-05
 */

#include "../Sensors/TinyGPSAdapter.h"
#include "../Enums/BaudRateTypes.h"


TinyGPSAdapter::TinyGPSAdapter(Stream* _gpsSerial)
    : gpsSerial(*_gpsSerial)
{
}


bool TinyGPSAdapter::initSensor()
{
    return true;
}


bool TinyGPSAdapter::isOperating() const
{
    uint32_t satelitesAmt = const_cast<TinyGPSAdapter*>(this)->gps.satellites.value();

    if (gps.location.isValid() && satelitesAmt >= 3)
        return true;

    return false;
}


const char* TinyGPSAdapter::getName()
{
    return "GPS";
}


double TinyGPSAdapter::getLatitude_deg()
{
    return gps.location.lat();
}


double TinyGPSAdapter::getLongitude_deg()
{
    return gps.location.lng();
}


uint16_t TinyGPSAdapter::getSattelitesAmt()
{
    return gps.satellites.value();
}


float TinyGPSAdapter::getSpeed_kmph()
{
    return gps.speed.kmph();
}


void TinyGPSAdapter::execute()
{
    while (gpsSerial.available())
        gps.encode(gpsSerial.read());
}
