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

#include "../Interfaces/IMotors.h"
//#include <stm32f103xb.h>
// https://github.com/stm32duino/wiki/wiki/HardwareTimer-library


class QuadXMotors : public Interfaces::IMotors
{
private:
    static const uint8_t FLMotorPin = PA6; // Front left
    static const uint8_t FRMotorPin = PA7; // Front right
    static const uint8_t BRMotorPin = PB0; // Back right
    static const uint8_t BLMotorPin = PB1; // Back left

    Enums::StateType motorsState;

    HardwareTimer motorsTimer;

    static const uint16_t MinPower = 1000;

public:
    QuadXMotors();

    bool initializeMotors() override;
    void updatePower(const ControlSticks& stickValues) override;
    void setMotorsState(Enums::StateType state) override;
    Enums::StateType getMotorsState() override;
};


#endif

