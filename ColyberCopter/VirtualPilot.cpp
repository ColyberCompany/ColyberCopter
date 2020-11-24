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


bool VirtualPilot::addFlightMode(FlightMode* flightMode)
{
    Iterator<FlightMode*>* iterator = flightModesArray.getIterator();

    while (iterator->hasNext())
        if (iterator->next()->getType() == flightMode->getType())
            return false; // flight mode instance of this type was already added

    flightModesArray.add(flightMode);
    return true;
}


bool VirtualPilot::initializeFlightModes()
{
    Iterator<FlightMode*>* iterator = flightModesArray.getIterator();
    bool result = true;

    while (iterator->hasNext())
        result = result && iterator->next()->initializeFlightMode();

    return result;
}


bool VirtualPilot::setFlightMode(FlightModeTypes flightModeType)
{
    FlightMode* flightModeToSet = getFlightModePtrByType(flightModeType);

    if (flightModeToSet == nullptr)
        return false;

    if (flightModeToSet == currentFlightMode)
        return true;

    executePrepareAndLeaveMethods(currentFlightMode, flightModeToSet);
    
    currentFlightMode = flightModeToSet;
}


void VirtualPilot::runVirtualPilot()
{
    ControlSticks virtualSticks(steeringData->throttle, steeringData->yaw,
                                steeringData->pitch, steeringData->roll);

    currentFlightMode->executeFlightModeLoop(virtualSticks);
    motors->updatePower(virtualSticks);
}


FlightModeTypes VirtualPilot::getCurrentFlightModeType()
{
    return currentFlightMode->getType();
}



FlightMode* VirtualPilot::getFlightModePtrByType(FlightModeTypes flightModeType)
{
    Iterator<FlightMode*>* iter = flightModesArray.getIterator();

    while (iter->hasNext())
    {
        FlightMode* temp = iter->next();
        if (temp->getType() == flightModeType)
            return temp;
    }

    return nullptr;
}


void VirtualPilot::executePrepareAndLeaveMethods(const FlightMode* oldFlightMode, const FlightMode* newFlightMode)
{
    Iterator<FlightMode*>* iterator = flightModesArray.getIterator();
    while (iterator->hasNext())
    {
        FlightMode* checked = iterator->next();
        bool wasUsed = oldFlightMode->checkIfSuperiorOrEqualOf(checked);
        bool willBeUsed = newFlightMode->checkIfSuperiorOrEqualOf(checked);

        if (!wasUsed && willBeUsed)
            checked->prepare();
        else if (wasUsed && !willBeUsed)
            checked->leave();
    }
}

