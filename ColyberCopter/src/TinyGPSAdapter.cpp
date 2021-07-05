#include "../Sensors/TinyGPSAdapter.h"
#include "../Enums/BaudRateTypes.h"

bool TinyGPSAdapter::initialize()
{
    TinyGPSPlus gps;
    
    Serial2.begin(Enums::BAUD_9600);

    if (gps.charsProcessed() < 10 && gps.encode(Serial.read()) == 0) 
        return false;
    
    return true;
}