/**
 * @file FloatAxesVector.h
 * @author Jan Wielgus
 * @brief This class is used to create one, two or three
 * dimensional vector to store different sized vector
 * in a unified way.
 * @date 2020-11-25
 * 
 */

#ifndef FLOATAXISVECTOR_H
#define FLOATAXISVECTOR_H

#include "Enums/AxisType.h"


class FloatAxisVector
{
private:
    float* valuesArray;
    uint8_t axesAmt; // at most 3

public:
    /**
     * @brief Parametrized ctor.
     * @param axesAmt Amount of axes that this vector will have.
     */
    FloatAxisVector(uint8_t axesAmt)
    {
        if (axesAmt > 3)
            axesAmt = 3;

        this->axesAmt = axesAmt;
        valuesArray = new float[axesAmt];
    }

    /**
     * @brief Copy ctor.
     * @param other Other vector to make a copy.
     */
    FloatAxisVector(const FloatAxisVector& other)
    {
        axesAmt = other.axesAmt;
        valuesArray = new float[axesAmt];
    }

    /**
     * @brief Assignment operator. Changes amount of axes and their values.
     * @param other Original axis vector to copy.
     */
    FloatAxisVector& operator=(const FloatAxisVector& other)
    {
        if (this != &other)
        {
            if (axesAmt != other.axesAmt)
            {
                delete[] valuesArray;
                axesAmt = other.axesAmt;
                valuesArray = new float[axesAmt];
            }

            for (int i = 0; i < axesAmt; i++)
                    valuesArray[i] = other.valuesArray[i];
        }

        return *this;
    }

    /**
     * @param axis Axis to get value from
     * (for one dimensional types put AxisX)
     * @return Value on specified axis.
     */
    float getAxis(Enums::AxisType axis)
    {
        return valuesArray[(uint8_t)axis];
    }

    /**
     * @brief Setter of one axis value. 
     * @param value New value for the axis.
     * @param axis Which axis.
     */
    void setAxis(float value, Enums::AxisType axis)
    {
        valuesArray[(uint8_t)axis] = value;
    }
};


#endif
