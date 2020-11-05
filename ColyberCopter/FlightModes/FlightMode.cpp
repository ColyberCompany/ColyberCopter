/**
 * @file FlightMode.cpp
 * @author Jan Wielgus
 * @date 2020-07-31
 * 
 */

#include "FlightMode.h"

using Enums::FlightModeTypes;


ControlSticks FlightMode::virtualSticks;


FlightMode::FlightMode(FlightModeTypes flightModeType, FlightMode* baseFlightMode, float deltaTime)
    : type(flightModeType), baseFlightMode(baseFlightMode), DeltaTime(deltaTime)
{
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


bool FlightMode::initializeFlightMode()
{
    return true;
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


void FlightMode::resetSticks()
{
    virtualSticks.setThrottle(0);
    virtualSticks.setYaw(0);
    virtualSticks.setPitch(0);
    virtualSticks.setRoll(0);
}
