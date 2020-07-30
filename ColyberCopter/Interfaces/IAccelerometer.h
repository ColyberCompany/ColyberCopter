/**
 * @file IAccelerometer.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IACCELEROMETER_H
#define IACCELEROMETER_H

#include "Common/Vector3.h"


namespace Interfaces
{
    class IAccelerometer
    {
    public:
        virtual ~IAccelerometer() {}

        virtual bool initializeAccelerometer() = 0;
        virtual vector3Float getNormAcceleration() = 0;
        virtual void calibrateAccelerometer(int16_t samplesToAverage) = 0;
        virtual vector3Int16 getAccelerometerOffset() = 0;
        virtual void setAccelerometerOffset(vector3Int16 offset) = 0;
        virtual void setAccelerometerOffset(int16_t offX, int16_t offY, int16_t offZ) = 0;
    };
}


#endif