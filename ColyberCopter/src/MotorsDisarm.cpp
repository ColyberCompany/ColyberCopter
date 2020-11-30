/**
 * @file MotorsDisarm.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "Failsafe/FailsafeActions/MotorsDisarm.h"

using Interfaces::IMotors;
using Enums::StateType;


MotorsDisarm::MotorsDisarm(IMotors& _motors)
    : motors(_motors)
{
}


void MotorsDisarm::execute()
{
    motors.setMotorsState(StateType::Disabled);
}
