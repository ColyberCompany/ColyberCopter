/**
 * @file AltitudeCalculation.h
 * @author Aleksy Walczak (aleksyww@gmail.com)
 * @brief Altitude calculation madde only by a barometer
 * @date 2021-08-19
 * 
 */

#ifndef ALTITUDECALCULATION_H
#define ALTITUDECALCULATION_H

#include "../../Interfaces/IPositionCalculation.h"
#include "../../Instances/SensorInstances.h"


class AltitudeCalculation : public Interfaces::IPositionCalculation
{
    float altitude_m;
    float p0_hPa = 1023;
    float p_hPa;
    float T_C = 15.f;
public:
    void updatePositionCalculation() override
    {
        p_hPa = Instance::baro.getPressure_hPa();
        T_C = Instance::temperature.getTemperature_degC();
        altitude_m = Common::Utils::calculateAltitude(p0_hPa, p_hPa, T_C);
    }

    Common::vector3Double getPosition() override
    {
        return Common::vector3Double(0, 0, altitude_m);
    }

    void resetAltitude() override
    {
        p0_hPa = Instance::baro.getPressure_hPa();
    }
};


#endif
