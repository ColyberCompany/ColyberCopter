/**
 * @file NoPosCalcTemp.h
 * @brief Temporary file when there is any position calculation.
 * @date 2020-11-27
 * 
 */

#ifndef NOPOSCALCTEMP_H
#define NOPOSCALCTEMP_H

#include "../../Interfaces/IPositionCalculation.h"


class NoPosCalcTemp : public Interfaces::IPositionCalculation
{
public:
    void updatePositionCalculation() override
    {
    }

    vector3Double getPosition() override
    {
        return vector3Double(0, 0, 0);
    }
};


#endif

