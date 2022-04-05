/**
 * @file calibration.h
 * @author Jan Wielgus
 * @brief Calibration values for sensors
 * @date 2022-03-30
 */

#ifndef CALIBRATION_h
#define CALIBRATION_h

#include "Common/Vector3.h"


namespace Calibration
{
    using Common::vector3Float;

    inline constexpr vector3Float AccOffset = {0.017505502, 0.004973429, 0.026660183};
    inline constexpr vector3Float AccScale = {0.99603490, 0.99502618, 0.98504321};

    inline constexpr vector3Float MagnOffset = {0.33669f, 72.428757f, 24.6033812f};
    inline constexpr vector3Float MagnScale = {0.00245227f, 0.00249f, 0.0021015f};

    inline constexpr vector3Float GyroOffset = {-2.0812696,  1.9969787, -0.2270786};
}


#endif

