/**
 * @file TinyGPSAdapter.h
 * @author Antoni Wielgus
 * @date 2021-07-05
 * 
 */


#include "../Sensors/TinyGPSAdapter.h"
#include "../Enums/BaudRateTypes.h"


TinyGPSAdapter::TinyGPSAdapter(Stream& _gpsSerial)
    : gpsSerial(_gpsSerial)
{
}

bool TinyGPSAdapter::initSensor()
{
    HardwareSerial
    gpsSerial.begin(Enums::BAUD_9600);

    return true;
}

bool TinyGPSAdapter::isOperating() const
{
    if (gps.location.isValid() && gps.satellites.value() >= 3)
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

uint8_t TinyGPSAdapter::getSattelitesAmt()
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
