/**
 * @file UnarmedFlightMode.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-03-30
 * 
 */

#include "../FlightModes/UnarmedFlightMode.h"
#include "../Instances/MotorsInstance.h"


UnarmedFlightMode::UnarmedFlightMode()
    : FlightMode(Enums::FlightModeTypes::UNARMED, nullptr)
{
}


void UnarmedFlightMode::leave()
{
    Instance::motors.setState(Enums::StateType::Enabled);
}


void UnarmedFlightMode::prepare()
{
    Instance::motors.setState(Enums::StateType::Disabled);
}


const char* UnarmedFlightMode::getName()
{
    return "unarmed";
}


void UnarmedFlightMode::flightModeLoop(ControlSticks& inputOutputSticks)
{
    if (Instance::motors.getState() == Enums::StateType::Enabled)
        Instance::motors.setState(Enums::StateType::Disabled);
}
