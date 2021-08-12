/**
 * @file Accelerometer.h
 * @author Jan Wielgus
 * @brief Base class for all accelerometers.
 * @date 2021-08-11
 */

#ifndef __ACCELEROMETER_H__
#define __ACCELEROMETER_H__

#include "Sensor.h"
#include "../../Common/Vector3.h"


class Accelerometer : public Sensor
{
public:
    Accelerometer()
        : Sensor(Enums::SensorTypes::ACCELEROMETER)
    {
    }
    
    virtual ~Accelerometer() {}

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


#endif // __ACCELEROMETER_H__
