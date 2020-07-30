/**
 * @file IBarometer.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IBAROMETER_H
#define IBAROMETER_H


namespace Interfaces
{
    class IBarometer
    {
    public:
        virtual ~IBarometer() {}

        virtual bool initializeBarometer() = 0;
        virtual float getPressure_hPa() = 0;
    };
}


#endif