/**
 * @file IPositionCalculation.h
 * @author Jan Wielgus
 * @brief Interface for position calculation classes.
 * @date 2020-09-01
 * 
 */

#ifndef IPOSITIONCALCULATION_H
#define IPOSITIONCALCULATION_H

#include "../Common/Vector3.h"


namespace Interfaces
{
    class IPositionCalculation
    {
    public:
        virtual ~IPositionCalculation() {}

        virtual void updatePositionCalculation() = 0;
        virtual Common::vector3Double getPosition() = 0;
        virtual void resetAltitude() = 0;
    };
}


#endif
