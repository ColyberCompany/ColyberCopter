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


#include "Interfaces/IMotors.h"

class QuadXMotors : public Interfaces::IMotors
{
private:
    Enums::StateType motorsState;

public:
    QuadXMotors();

    bool initializeMotors() override;
    void updatePower(const ControlSticks& stickValues) override;
    void setMotorsState(Enums::StateType state) override;
};


#endif

