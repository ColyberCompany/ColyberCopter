/**
 * @file Quaternion.h
 * @author Aleksy Walczak (aleksyww@gmail.com)
 * @date 2021-08-17
 * 
 */

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"
#include <cmath>


namespace Common
{
    struct Quaternion
    {
        float r;
        float i;
        float j;
        float k;

        Quaternion() {}

        Quaternion(float r, float i, float j, float k)
        {
            this->r = r;
            this->i = i;
            this->j = j;
            this->k = k;
        }

        float getHalfAngle() const
        {
            return acos(r);
        }

        Quaternion inverse() const
        {
            return Quaternion(r, -i, -j, -k);
        }

        vector3Float rotate3DVector(const vector3Float& vect) const
        {
            float R1 = 1 - 2*(j * j + k * k);
            float R2 = 2*(i * j - k * r);
            float R3 = 2*(i * k + j * r);

            float R4 = 2*(i * j + k * r);
            float R5 = 1 - 2*(i * i + k * k);
            float R6 = 2*(j * k - i * r);

            float R7 = 2*(i * k - j * r);
            float R8 = 2*(j * k + i * r);
            float R9 = 1 - 2*(i * i + j * j);

            float x = R1 * vect.x + R2 * vect.y + R3 * vect.z;
            float y = R4 * vect.x + R5 * vect.y + R6 * vect.z;
            float z = R7 * vect.x + R8 * vect.y + R9 * vect.z;

            return vector3Float(x, y, z);
        }

        Quaternion operator*(const Quaternion& rhs)
        {
            return Quaternion(r*rhs.r - i*rhs.i - j*rhs.j - k*rhs.k,
                              r*rhs.i + i*rhs.r + j*rhs.k - k*rhs.j,
                              r*rhs.j - i*rhs.k + j*rhs.r + k*rhs.i,
                              r*rhs.k + i*rhs.j - j*rhs.i + k*rhs.r);
        }
    };
}


#endif
