#ifndef UTILS_H
#define UTILS_H

#include "Vector3.h"
#include <Arduino.h>

namespace Common
{
    namespace Utils
    {
        template <typename T>
        inline void printVector3(const T& toShow, Stream& stream = Serial, const char* separator = "\t")
        {
            stream.print(toShow.x);
            stream.print(separator);
            stream.print(toShow.y);
            stream.print(separator);
            stream.println(toShow.z);
        }


        /**
         * @brief Fast inverse square-root.
         * See: http://en.wikipedia.org/wiki/Fast_inverse_square_root.
         * @param x Number which square root will be extracted.
         * @return Square root of parameter x.
         */
        inline float invSqrt(float x)
        {
            float halfx = 0.5f * x;
            float y = x;
            long i = *(long*)&y;
            i = 0x5f3759df - (i>>1);
            y = *(float*)&i;
            y = y * (1.5f - (halfx * y * y));
            return y;
        }


        /**
         * @brief Calculate altitude relative to some point with pressure0 pressure.
         * @param pressure0 pressure on the ground level (currentPressure and pressure0 have to be in the same unit).
         * @param currentPressure pressure in your position (currentPressure and pressure0 have to be in the same unit).
         * @param temperature_degC temperature in degrees celsius.
         * @return calculated altitude above ground level.
         */
        inline constexpr float calculateAltitude(float pressure0, float currentPressure, float temperature_degC)
        {
            return (pow(currentPressure / pressure0, -0.19f) - 1) * (temperature_degC + 273.15f)  * 153.846f;
        }


        class
        {
            Stream* stream = &Serial;
            char separator = '\t';

        public:
            template <class T>
            void operator()(T value) const {
                stream->println(value);
            }

            template <class T, class... Args>
            void operator()(T value, Args... args) const
            {
                stream->print(value);
                stream->print(separator);
                operator()(args...);
            }

            void setStream(Stream* stream)
            {
                this->stream = stream;
            }

            void setSeparator(char separator)
            {
                this->separator = separator;
            }
        } print;
    }
}


#endif
