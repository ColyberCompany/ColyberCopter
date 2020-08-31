/**
 * @file IPositionCalculation.h
 * @author Jan Wielgus
 * @brief Interface for position calculation classes.
 * @date 2020-09-01
 * 
 */

#ifndef IPOSITIONCALCULATION_H
#define IPOSITIONCALCULATION_H


namespace Interfaces
{
    class IPositionCalculation
    {
    public:
        virtual ~IPositionCalculation() {}

        virtual void updatePositionCalculation() = 0;
        virtual double getLongitude_deg() = 0;
        virtual double getLatitude_deg() = 0;
        virtual float getAltitude_m() = 0;
    };
}


#endif
