/**
 * @file SimpleMS5611Handler.h
 * @author Jan Wielgus
 * @brief Improved btaining acc ang gyro readings using SimpleHMC5883L library.
 * @date 2021-08-14
 */

#ifndef SIMPLEMS5611CONTINUOUS_H
#define SIMPLEMS5611CONTINUOUS_H

#include "Base/Barometer.h"
#include "Base/TemperatureSensor.h"
#include <SimpleMS5611.h>
#include <IExecutable.h>
#include <AverageFilter.h>


class SimpleMS5611Handler : private SimpleMS5611, public Barometer, public TemperatureSensor, public IExecutable
{
    AverageFilter<float> pressureFilter;
    float smoothPressure_mbar = 1000.f;
    uint8_t pressureReadingsCounter = 0; // used to get temperature every 20th measurement, from 1 to PressurePerTemperatureRequests, 0 indicates first pressure request
    
    static const uint8_t PressurePerTemperatureRequests = 19; // How many pressure requests are per one temperature request


public:
    SimpleMS5611Handler();

    float getPressure_hPa() override {
        return smoothPressure_mbar;
    }
    float getTemperature_degC() override {
        return SimpleMS5611::getTempereture();
    }
    const char* getName() override {
        return "ms5611";
    }

    using SimpleMS5611::RequestWaitTime_us;

private:
    bool init_priv() override;

    /**
     * @brief Reads pressure and, every 20th, reads temperature.
     */
    void execute() override;

    bool shouldGetPressureAndRequestPressure();
    bool shouldGetPressureAndRequestTemperature();
    bool shouldGetTemperatureAndRequestPressure();
    void updateSmoothPressure();
};



inline bool SimpleMS5611Handler::shouldGetPressureAndRequestPressure()
{
    return pressureReadingsCounter >= 1 && pressureReadingsCounter < PressurePerTemperatureRequests;
}


inline bool SimpleMS5611Handler::shouldGetPressureAndRequestTemperature()
{
    return pressureReadingsCounter == PressurePerTemperatureRequests;
}


inline bool SimpleMS5611Handler::shouldGetTemperatureAndRequestPressure()
{
    return pressureReadingsCounter == (PressurePerTemperatureRequests + 1);
}


#endif
