#ifndef UTILS_H
#define UTILS_H

#include "Vector3.h"

namespace Common
{
    namespace Utils
    {
        template <typename T>
        void printVector3(Stream& serialNumber,const vector3<T>& toShow, const char* separator = "\t")
        {
            serialNumber.print(toShow.x);
            serialNumber.print(separator);
            serialNumber.print(toShow.y);
            serialNumber.print(separator);
            serialNumber.println(toShow.z);
        }


        /**
         * @brief Fast inverse square-root.
         * See: http://en.wikipedia.org/wiki/Fast_inverse_square_root.
         * @param x Number which square root will be extracted.
         * @return Square root of parameter x.
         */
        float invSqrt(float x);


        /**
         * @brief Calculate altitude relative to some point with pressure0 pressure.
         * @param pressure0 pressure on the ground level (currentPressure and pressure0 have to be in the same unit).
         * @param currentPressure pressure in your position (currentPressure and pressure0 have to be in the same unit).
         * @param temperature_degC temperature in degrees celsius.
         * @return calculated altitude above ground level.
         */
        float calculateAltitude(float pressure0, float currentPressure, float temperature_degC);
    }
}


#endif
