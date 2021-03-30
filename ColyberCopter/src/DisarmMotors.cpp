/**
 * @file MotorsDisarm.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "../Failsafe/FailsafeActions/DisarmMotors.h"
#include "../Instances/MotorsInstance.h"

using Enums::StateType;


void DisarmMotors::execute()
{
    Instance::motors.setState(StateType::Disabled);
}
