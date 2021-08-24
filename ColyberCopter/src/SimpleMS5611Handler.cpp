/**
 * @file SimpleMS5611Handler.cpp
 * @author Jan Wielgus
 * @date 2021-08-14
 */

#include "../Sensors/SimpleMS5611Handler.h"


SimpleMS5611Handler::SimpleMS5611Handler()
    : pressureFilter(PressurePerTemperatureRequests + 1)
{
    // Initialize average filter with initial averate of 1000 mbar
    for (uint8_t i = 0; i < PressurePerTemperatureRequests + 1; ++i)
        pressureFilter.update(1000.f);
}


bool SimpleMS5611Handler::initSensor()
{
    return SimpleMS5611::initialize();
}


float SimpleMS5611Handler::getPressure_hPa()
{
    return smoothPressure_mbar;
}


const char* SimpleMS5611Handler::getName()
{
    return "ms5611 baro";
}


void SimpleMS5611Handler::execute()
{
    if (shouldGetPressureAndRequestPressure())
    {
        SimpleMS5611::getRawPressureFromDevice();
        SimpleMS5611::requestPressureFromDevice();
    }
    else if (shouldGetPressureAndRequestTemperature())
    {
        SimpleMS5611::getRawPressureFromDevice();
        SimpleMS5611::requestTemperatureFromDevice();
    }
    else if (shouldGetTemperatureAndRequestPressure())
    {
        SimpleMS5611::getRawTemperatureFromDevice();
        SimpleMS5611::requestPressureFromDevice();
        
        pressureReadingsCounter = 0; // reset counter
    }
    else // first pressure request, if actionCounter is 0 at the beginning
    {
        // Should run this only once
        SimpleMS5611::requestPressureFromDevice();
    }

    SimpleMS5611::calculatePressureAndTemperatureFromRawData();
    updateSmoothPressure();

    pressureReadingsCounter++;
}


void SimpleMS5611Handler::updateSmoothPressure()
{
    // At the beginning pressure is negative for a moment
    if (pressure_mbar < 0)
        pressure_mbar = 0;

    float newPresure_mbar = pressureFilter.update(pressure_mbar);

    if (abs(smoothPressure_mbar - newPresure_mbar) > 1)
		smoothPressure_mbar = smoothPressure_mbar*0.72f + newPresure_mbar*0.28f;
	else
		smoothPressure_mbar = smoothPressure_mbar*0.96f + newPresure_mbar*0.04f;
}
