/**
 * @file VirtualPilot.cpp
 * @author Jan Wielgus
 * @date 2020-11-11
 * 
 */

#include "../VirtualPilot.h"
#include "../Instances.h"
#include "../Communication/CommData.h"

using Interfaces::IMotors;
using Enums::StateType;
using Enums::FlightModeTypes;


VirtualPilot::VirtualPilot(IMotors& _motors, FlightMode& initialFlightMode)
    : motors(_motors)
{
    this->currentFlightMode = &initialFlightMode;
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

    Instance::debMes.showMessage("Flight mode has been changed to:");
    Instance::debMes.showMessage(currentFlightMode->getName());
}


void VirtualPilot::runVirtualPilot()
{
    ControlSticks virtualSticks(commData.pilot.stick.throttle,
                                commData.pilot.stick.yaw,
                                commData.pilot.stick.pitch,
                                commData.pilot.stick.roll);

    currentFlightMode->executeFlightModeLoop(virtualSticks);
    motors.updatePower(virtualSticks);
}


FlightModeTypes VirtualPilot::getCurrentFlightModeType()
{
    return currentFlightMode->getType();
}


void VirtualPilot::execute()
{
    runVirtualPilot();
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

