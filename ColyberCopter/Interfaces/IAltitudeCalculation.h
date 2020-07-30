/**
 * @file IAltitudeCalculation.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IALTITUDECALCULATION_H
#define IALTITUDECALCULATION_H


namespace Interfaces
{
    class IAltitudeCalculation
    {
    public:
        virtual ~IAltitudeCalculation() {}

        virtual void updateAltitudeCalculation() = 0;
        virtual float getAltitude_m() = 0;
    };
}


#endif
