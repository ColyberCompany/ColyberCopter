/**
 * @file VirtualPilot.cpp
 * @author Jan Wielgus
 * @date 2020-11-11
 * 
 */

#include "VirtualPilot.h"

using Interfaces::IMotors;
using Enums::StateType;
using Enums::FlightModeTypes;


VirtualPilot::VirtualPilot(IMotors* motors, FlightMode* initialFlightMode, const DataFromRmtCtrl* steeringData)
{
    this->motors = motors;
    this->currentFlightMode = initialFlightMode;
    this->steeringData = steeringData;
}


void VirtualPilot::runVirtualPilot()
{
    updateFlightModesSticksWithRmtCtrlValues();
    executeCurrentFlightMode();
    updateMotorsPower();
}


bool VirtualPilot::setFlightMode(FlightMode* flightModeToSet)
{
    if (flightModeToSet == nullptr)
        return false;
    
    currentFlightMode = flightModeToSet;




    // TODO: there is the hard part.
    // need to call leave() and prepare() methods for certain flight modes.
    // figure out how to do that without creating flight modes list here.
    // maybe create that list in the constructor of FlightMode and this list
    // will be a static field of that class.
}


FlightModeTypes VirtualPilot::getCurrentFlightModeType()
{
    return currentFlightMode->getType();
}



void VirtualPilot::updateFlightModesSticksWithRmtCtrlValues()
{
    FlightMode::getVirtualSticksPtr()->set(steeringData->throttle, steeringData->yaw,
                                            steeringData->pitch, steeringData->roll);
}


void VirtualPilot::executeCurrentFlightMode()
{
    if (motors->getMotorsState() == StateType::Enabled)
        currentFlightMode->armedLoop();
    else
        currentFlightMode->disarmedLoop();
}


void VirtualPilot::updateMotorsPower()
{
    motors->updatePower(*FlightMode::getVirtualSticksPtr());
}

