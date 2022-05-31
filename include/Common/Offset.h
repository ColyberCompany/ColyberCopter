/**
 * @file Offset.h
 * @brief Object version of FusionOffset with changable parameters.
 * @date 2022-05-24
 */

#ifndef OFFSET_H
#define OFFSET_H

#include "Vector3.h"
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


/**
 * @brief Offset class dynamically calculates offset of input value
 * (how much it is displaced from 0 when it is in threshold).
 */
class Offset
{
    float CutoffFrequency_Hz;
    float Timeout_s;
    float Threshold;

    float filterCoefficient;
    uint32_t timeout_samples;
    uint32_t timer_samples;
    Common::vector3Float offset;

public:
    /**
     * @brief Ctor.
     * @param sampleRate Offset update sample rate in Hz.
     * @param cutoffFreq Larger makes value faster converge to 0 (more aggressive offset calculation)
     * (offset is updated only when value is in threshold).
     * @param timeout_s How much time value have to be within threshold to enable offset update.
     * @param threshold Maximum and minimum value at which after timeout offset is updated.
     */
    Offset(uint16_t sampleRate, float cutoffFreq, float timeout_s, float threshold)
    {
        CutoffFrequency_Hz = cutoffFreq;
        Timeout_s = timeout_s;
        Threshold = threshold;

        filterCoefficient = 2.0f * (float) M_PI * CutoffFrequency_Hz * (1.0f / (float) sampleRate);
        timeout_samples = Timeout_s * sampleRate;
        timer_samples = 0;
        offset = {};
    }

    /**
     * @brief Process next value. Always pass new value and use that returned by that method.
     * @param value New value.
     * @return New output with newest offset.
     */
    Common::vector3Float update(Common::vector3Float value)
    {
        // Subtract offset from value
        value -= offset;

        // Reset timer if value not stationary
        if ((fabs(value.x) > Threshold) || (fabs(value.y) > Threshold) || (fabs(value.z) > Threshold)) {
            timer_samples = 0;
            return value;
        }

        // Increment timer while value stationary
        if (timer_samples < timeout_samples) {
            timer_samples++;
            return value;
        }

        // Adjust offset if timer has elapsed
        offset += value * filterCoefficient;
        return value;
    }
};


#endif
