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


struct vector3Float
{
    float x;
    float y;
    float z;

    vector3Float() {}
    
    vector3Float(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};


struct vector3Int16
{
    int16_t x;
    int16_t y;
    int16_t z;
};


#endif
