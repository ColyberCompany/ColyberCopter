/**
 * @file QuadXMotors.cpp
 * @author Jan Wielgus
 * @date 2020-11-05
 * 
 */

#include "QuadXMotors.h"

using Interfaces::IMotors;
using Enums::StateType;


QuadXMotors::QuadXMotors()
{
    motorsState = StateType::Disabled;
}


bool QuadXMotors::initializeMotors()
{
    // TODO: implement initializeMotors() method
    return false;
}


void QuadXMotors::updatePower(const ControlSticks& stickValues)
{
    // TODO: implement updatePower() method
}


void QuadXMotors::setMotorsState(StateType state)
{
    motorsState = state;

    if (motorsState == StateType::Disabled)
    {
        ControlSticks zeroSticks;
        zeroSticks.set(0, 0, 0, 0);
        updatePower(zeroSticks);
    }
}
