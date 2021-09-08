/**
 * @file QuadXMotors.h
 * @author Jan Wielgus
 * @brief This is class for controlling quadrocopter (4 motors)
 * positioned in X shape.
 * @date 2020-11-05
 */

#ifndef QUADXMOTORS_H
#define QUADXMOTORS_H

#include "Motors.h"
#include <IExecutable.h>


class QuadXMotors : public Motors, public IExecutable
{
    static const PinName FLMotorPin = PA_6; // Front left
    static const PinName FRMotorPin = PA_7_ALT1; // Front right
    static const PinName BRMotorPin = PB_0_ALT1; // Back right
    static const PinName BLMotorPin = PB_1_ALT1; // Back left

    HardwareTimer timer;

    int16_t flPower;    // 0 - 1000
    int16_t frPower;    // 0 - 1000
    int16_t brPower;    // 0 - 1000
    int16_t blPower;    // 0 - 1000

public:
    QuadXMotors();

    bool initializeMotors() override;
    void setPower(const Common::ControlSticks& stickValues) override;

private:
    void execute() override;
};


#endif

