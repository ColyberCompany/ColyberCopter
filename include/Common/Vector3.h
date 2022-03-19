/**
 * @file Vector3.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#include <cstdint>


namespace Common
{
    template <class T>
    struct vector3
    {
        T x = {};
        T y = {};
        T z = {};

        constexpr vector3()
        {}

        constexpr vector3(T x, T y, T z):
            x(x),
            y(y),
            z(z)
        {}
    };

    typedef vector3<float> vector3Float;
    typedef vector3<double> vector3Double;

    typedef vector3<int16_t> vector3Int16;
    typedef vector3<int32_t> vector3Int32;
}


#endif
