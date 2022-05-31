/**
 * @file CalibrationIntertial.h
 * @author Jan Wielgus
 * @brief Calibration is based on Fusion library (https://github.com/xioTechnologies/Fusion).
 * @date 2022-05-31
 */

#ifndef __CALIBRATIONINERTIAL_h__
#define __CALIBRATIONINERTIAL_h__

#include "Common/Vector3.h"
extern "C" {
    #include "Fusion/FusionMath.h"
    #include "Fusion/FusionCalibration.h"
}

// Calibration: https://thecavepearlproject.org/2015/05/22/calibrating-any-compass-or-accelerometer-for-arduino/
// How to perform (acc but same as magn): https://www.youtube.com/watch?v=-1tmYPE7MAQ
// Magneto v1.2: https://sites.google.com/view/sailboatinstruments1/


class CalibrationIntertial
{
    friend class Accelerometer;
    friend class Gyroscope;

public:
    struct Calibration {
        FusionMatrix misalignment = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        FusionVector sensitivity = {1.0f, 1.0f, 1.0f};
        FusionVector offset = {0.0f, 0.0f, 0.0f};
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
        auto calibrated = FusionCalibrationInertial(
            {vector.x, vector.y, vector.z},
            calibration.misalignment,
            calibration.sensitivity,
            calibration.offset
        );
        return {calibrated.axis.x, calibrated.axis.y, calibrated.axis.z};
    }
};


#endif
