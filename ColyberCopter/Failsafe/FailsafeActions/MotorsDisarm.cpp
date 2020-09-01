/**
 * @file MotorsDisarm.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "MotorsDisarm.h"

using Interfaces::IMotors;
using Enums::StateType;


MotorsDisarm::MotorsDisarm(IMotors* motors)
{
    this->motors = motors;
}


void MotorsDisarm::execute()
{
    motors->setMotorsState(StateType::Disabled);
}
