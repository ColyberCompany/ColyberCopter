/**
 * @file Gyroscope.h
 * @author Jan Wielgus
 * @brief Base class for all gyroscopes.
 * @date 2021-08-11
 */

#ifndef __GYROSCOPE_H__
#define __GYROSCOPE_H__

#include "Sensor.h"
#include "../../Common/Vector3.h"


class Gyroscope : public Sensor
{
public:
    Gyroscope(Enums::SensorTypes type)
        : Sensor(type)
    {
    }

    virtual ~Gyroscope() {}

    virtual Common::vector3Float get_degPerSec() = 0;

    virtual float getX_degPerSec()
    {
        return get_degPerSec().x;
    }

    virtual float getY_degPerSec()
    {
        return get_degPerSec().y;
    }

    virtual float getZ_degPerSec()
    {
        return get_degPerSec().z;
    }
};


#endif // __GYROSCOPE_H__
