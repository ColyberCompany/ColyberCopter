/**
 * @file IGyroscope.h
 * @author Jan Wielgus
 * @brief Interface for all gyroscopes.
 * @date 2021-08-11
 */

#ifndef __IGYROSCOPE_H__
#define __IGYROSCOPE_H__

#include "../../Common/Vector3.h"


namespace Interfaces
{
    class IGyroscope
    {
    public:
        virtual ~IGyroscope() {}

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
}


#endif // __IGYROSCOPE_H__