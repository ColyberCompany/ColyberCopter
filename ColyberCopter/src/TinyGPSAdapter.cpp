/**
 * @file TinyGPSAdapter.h
 * @author Antoni Wielgus
 * @date 2021-07-05
 * 
 */


#include "../Sensors/TinyGPSAdapter.h"
#include "../Enums/BaudRateTypes.h"

TinyGPSAdapter::TinyGPSAdapter(SensorsMediator& sensorsMediator, Stream& _gpsSerial)
    : Sensor(Enums::SensorTypes::GPS, sensorsMediator), gpsSerial(_gpsSerial)
{
}

bool TinyGPSAdapter::initialize()
{
    gpsSerial.begin(Enums::BAUD_9600);

    return true;
}

void TinyGPSAdapter::execute()
{
    while(gpsSerial.available() > 0)
    {
        if(gps.encode(gpsSerial.read()))
        {
            sensorsMediator.updateLatLong(gps.location.lat(), gps.location.lng());
        }    
    }   
}

const char* getName() override
{
    return "GPS";
}
