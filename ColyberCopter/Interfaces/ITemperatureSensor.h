/**
 * @file ITemperatureSensor.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef ITEMPERATURESENSOR_H
#define ITEMPERATURESENSOR_H


namespace Interfaces
{
    class ITemperatureSensor
    {
    public:
        virtual ~ITemperatureSensor() {}

        virtual bool initializeTemperatureSensor() = 0;
        virtual float getTemperature() = 0;
    };
}


#endif