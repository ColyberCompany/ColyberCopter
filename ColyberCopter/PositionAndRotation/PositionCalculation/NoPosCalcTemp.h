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

    double getLongitude_deg() override
    {
        return 0;
    }

    double getLatitude_deg() override
    {
        return 0;
    }
    
    float getAltitude_m() override
    {
        return 0;
    }
};


#endif

