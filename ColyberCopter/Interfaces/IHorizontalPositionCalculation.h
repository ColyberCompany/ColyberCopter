/**
 * @file IHorizontalPositionCalculation.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IHORIZONTALPOSITIONCALCULATION_H
#define IHORIZONTALPOSITIONCALCULATION_H


namespace Interfaces
{
    class IHorizontalPositionCalculation
    {
    public:
        virtual ~IHorizontalPositionCalculation() {}

        virtual void updateHorizontalPositionCalculation() = 0;
        virtual double getLongitude_deg() = 0;
        virtual double getLatitude_deg() = 0;
    };
}


#endif
