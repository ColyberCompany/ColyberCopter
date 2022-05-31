/**
 * @file CalibrationMagnetic.h
 * @author Jan Wielgus
 * @brief Calibration is based on Fusion library (https://github.com/xioTechnologies/Fusion).
 * @date 2022-05-31
 */

#ifndef __CALIBRATIONMAGNETIC_h__
#define __CALIBRATIONMAGNETIC_h__

#include "Common/Vector3.h"
extern "C" {
    #include "Fusion/FusionMath.h"
    #include "Fusion/FusionCalibration.h"
}

// Calibration: https://thecavepearlproject.org/2015/05/22/calibrating-any-compass-or-accelerometer-for-arduino/
// How to perform (magn but same as acc): https://www.youtube.com/watch?v=MinV5V1ioWg
// Magneto v1.2: https://sites.google.com/view/sailboatinstruments1/


class CalibrationMagnetic
{
    friend class Magnetometer;

public:
    struct Calibration {
        FusionMatrix softIronMatrix = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        FusionVector hardIronOffset = {0.0f, 0.0f, 0.0f};
    };

private:
    Calibration calibration;

public:
    void setCalibration(Calibration calibration)
    {
        this->calibration = calibration;
    }

    Calibration getCalibration()
    {
        return calibration;
    }

protected:
    Common::vector3Float applyCalibration(Common::vector3Float vector)
    {
        auto calibrated = FusionCalibrationMagnetic(
            {vector.x, vector.y, vector.z},
            calibration.softIronMatrix,
            calibration.hardIronOffset
        );
        return {calibrated.axis.x, calibrated.axis.y, calibrated.axis.z};
    }
};


#endif
