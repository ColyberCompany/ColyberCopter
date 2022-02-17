/**
 * @file FlightMode.cpp
 * @author Jan Wielgus
 * @date 2020-07-31
 * 
 */

#include "FlightModes/FlightMode.h"
#include "config.h"

using Enums::FlightModeTypes;
using Common::ControlSticks;


FlightMode::FlightMode(FlightModeTypes flightModeType, FlightMode* baseFlightMode)
    : type(flightModeType), baseFlightMode(baseFlightMode)
{
}


bool FlightMode::checkIfSuperiorOrEqualOf(const FlightMode* flightModeToCheck) const
{
    if (flightModeToCheck == this) // TODO: Why don't just compare the type!? (It will enable to don't add each flight mode to the vp at the startup) >>> This won't work, because base flight mode of two flight modes could be the same type, but they are different flight modes.
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
