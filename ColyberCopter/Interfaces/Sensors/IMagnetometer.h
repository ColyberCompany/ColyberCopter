/**
 * @file IMagnetometer.h
 * @author Jan Wielgus
 * @brief Interface for all magnetometers.
 * @date 2021-08-11
 */

#ifndef __IMAGNETOMETER_H__
#define __IMAGNETOMETER_H__

#include "../../Common/Vector3.h"


namespace Interfaces
{
    class IMagnetometer
    {
    public:
        virtual ~IMagnetometer() {}

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

        virtual Common::vector3Int16 get_raw() = 0;

        virtual int16_t getX_raw()
        {
            return get_raw().x;
        }

        virtual int16_t getY_raw()
        {
            return get_raw().y;
        }

        virtual int16_t getZ_raw()
        {
            return get_raw().z;
        }
    };
}


#endif // __IMAGNETOMETER_H__