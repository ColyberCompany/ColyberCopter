/**
 * @file FlightMode.cpp
 * @author Jan Wielgus
 * @date 2020-07-31
 * 
 */

#include "FlightMode.h"

using Enums::FlightModeTypes;


FlightMode::FlightMode(FlightModeTypes flightModeType, FlightMode* baseFlightMode, float deltaTime)
    : type(flightModeType), baseFlightMode(baseFlightMode), DeltaTime(deltaTime)
{
}


bool FlightMode::checkIfSuperiorOrEqualOf(const FlightMode* flightModeToCheck) const
{
    if (flightModeToCheck == this)
        return true;

    else if (baseFlightMode != nullptr)
        return baseFlightMode->checkIfSuperiorOrEqualOf(flightModeToCheck);

    else
        return false;
}


Enums::FlightModeTypes FlightMode::getType()
{
    return type;
}


bool FlightMode::initializeFlightMode()
{
    return true;
}


void FlightMode::executeFlightModeLoop(ControlSticks& inputOutputSticks)
{
    flightModeLoop(inputOutputSticks);
    if (baseFlightMode != nullptr)
        baseFlightMode->executeFlightModeLoop(inputOutputSticks);
}


void FlightMode::resetSticks(ControlSticks& sticks)
{
    sticks.setThrottle(0);
    sticks.setYaw(0);
    sticks.setPitch(0);
    sticks.setRoll(0);
}
