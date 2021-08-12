/**
 * @file Magnetometer.h
 * @author Jan Wielgus
 * @brief Base class for all magnetometers.
 * @date 2021-08-11
 */

#ifndef __MAGNETOMETER_H__
#define __MAGNETOMETER_H__

#include "Sensor.h"
#include "../../Common/Vector3.h"


class Magnetometer : public Sensor
{
public:
    Magnetometer()
        : Sensor(Enums::SensorTypes::MAGNETOMETER)
    {
    }

    virtual ~Magnetometer() {}

    virtual Common::vector3Float get_norm() = 0;

    virtual float getX_norm()
    {
        return get_norm().x;
    }

    virtual float getY_norm()
    {
        return get_norm().y;
    }

    virtual float getZ_norm()
    {
        return get_norm().z;
    }
};


#endif // __MAGNETOMETER_H__