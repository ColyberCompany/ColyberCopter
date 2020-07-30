/**
 * @file ISensorData.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef ISENSORDATA_H
#define ISENSORDATA_H

#include "Vector3.h"


namespace Interfaces
{
    class ISensorData
    {
    public:
        virtual ~ISensorData() {}

        virtual vector3Float getAcc_normVector() = 0;
        virtual vector3Float getGyro_degPerSec() = 0;
        virtual vector3Float getMag_normVector() = 0;
        virtual float getPressure_hPa() = 0;
        virtual double getLatitude_deg() = 0;
        virtual double getLongitude_deg() = 0;
        virtual float getBottomRangefinderDistance_m() = 0;
        virtual float getTemperature_degC() = 0;
    };
}


#endif