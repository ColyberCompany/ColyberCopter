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
    // self-add this flight mode after instantiation
    virtualPilot->addFlightMode(this);
}


// TODO: implementation of the rest of the class
