/**
 * @file Vector3.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#ifdef ARDUINO
    #include <Arduino.h>
#endif


template <class T>
struct vector3
{
    T x;
    T y;
    T z;

    vector3() {}

    vector3(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

typedef vector3<float> vector3Float;
typedef vector3<double> vector3Double;

typedef vector3<int16_t> vector3Int16;
typedef vector3<int32_t> vector3Int32;


#endif
