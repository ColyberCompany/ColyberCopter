/**
 * @file ICompass.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef ICOMPASS_H
#define ICOMPASS_H

#include "Common/Vector3.h"


namespace Interfaces
{
    class ICompass
    {
    public:
        virtual ~ICompass() {}

        virtual bool initializeCompass() = 0;
        virtual vector3Float getNormCompassData() = 0;
        virtual void calibrateCompass(int16_t samplesToAverage) = 0;
        virtual vector3Int16 getCompassOffset() = 0;
        virtual void setCompassOffset(vector3Int16 offset) = 0;
        virtual void setCompassOffset(int16_t offX, int16_t offY, int16_t offZ) = 0;
    };
}


#endif
