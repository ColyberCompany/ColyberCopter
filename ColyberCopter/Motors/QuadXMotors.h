/**
 * @file QuadXMotors.h
 * @author Jan Wielgus
 * @brief This is class for controlling quadrocopter (4 motors)
 * positioned in X shape.
 * @date 2020-11-05
 * 
 */


#ifndef QUADXMOTORS_H
#define QUADXMOTORS_H

#include "Motors.h"
//#include <stm32f103xb.h>
// https://github.com/stm32duino/wiki/wiki/HardwareTimer-library


class QuadXMotors : public Motors
{
    static const PinName FLMotorPin = PA_6; // Front left
    static const PinName FRMotorPin = PA_7_ALT1; // Front right
    static const PinName BRMotorPin = PB_0_ALT1; // Back right
    static const PinName BLMotorPin = PB_1_ALT1; // Back left

    HardwareTimer motorsTimer;

    static const uint16_t MinPower = 1000;

public:
    QuadXMotors();

    bool initializeMotors() override;
    void updatePower(const Common::ControlSticks& stickValues) override;
};


#endif

