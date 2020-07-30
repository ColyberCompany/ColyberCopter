/**
 * @file IGyroscope.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IGYROSCOPE_H
#define IGYROSCOPE_H

#include "Common/Vector3.h"


namespace Interfaces
{
    class IGyroscope
    {
    public:
        virtual ~IGyroscope() {}

        virtual bool initializeGyroscope() = 0;
        virtual vector3Float getNormRotation() = 0;
        virtual void calibrateGyroscope(int16_t samplesToAverage) = 0;
        virtual vector3Int16 getGyroscopeOffset() = 0;
        virtual void setGyroscopeOffset(vector3Int16 offset) = 0;
        virtual void setGyroscopeOffset(int16_t offX, int16_t offY, int16_t offZ) = 0;
    };
}


#endif