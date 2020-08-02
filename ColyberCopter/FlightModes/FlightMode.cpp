/**
 * @file FlightMode.cpp
 * @author Jan Wielgus
 * @date 2020-07-31
 * 
 */

#include "FlightMode.h"

using Enums::FlightModeTypes;
using Interfaces::IVirtualPilot;


ControlSticks FlightMode::virtualSticks;


FlightMode::FlightMode(FlightModeTypes flightModeType, FlightMode* baseFlightMode, IVirtualPilot* virtualPilot)
    : type(flightModeType), baseFlightMode(baseFlightMode)
{
    virtualPilotPtr = virtualPilot;
}


bool FlightMode::initializeFlightMode()
{
    // self-add this flight mode after instantiation
    virtualPilotPtr->addFlightMode(this);

    return true;
}


bool FlightMode::checkIfRelated(const FlightMode* flightModeToCheck)
{
    if (flightModeToCheck == this)
        return true;

    else if (baseFlightMode != nullptr)
        return baseFlightMode->checkIfRelated(flightModeToCheck);

    else
        return false;
}


Enums::FlightModeTypes FlightMode::getType()
{
    return type;
}


ControlSticks* FlightMode::getVirtualSticksPtr()
{
    return &virtualSticks;
}


void FlightMode::runBaseFlightMode()
{
    if (baseFlightMode != nullptr)
        baseFlightMode->run();
}


void FlightMode::runBaseFlightModeIdleLoop()
{
    if (baseFlightMode != nullptr)
        baseFlightMode->idleLoop();
}
