/**
 * @file FailsafeActions.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Definitions of all FailsafeAction classes
 * @date 2021-04-08
 * 
 */

#include "Failsafe/FailsafeActions/DisarmMotors.h"
// other failsafe actions...
#include "Instances/MainInstances.h"
#include "Instances/MotorsInstance.h"

using namespace FailsafeActions;


void DisarmMotors::execute()
{
    Instance::motors.setState(Enums::StateType::Disabled);
    Instance::virtualPilot.setFlightMode(Enums::FlightModeTypes::UNARMED);
}


// other failsafe actions...
