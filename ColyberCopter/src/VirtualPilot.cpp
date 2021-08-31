/**
 * @file VirtualPilot.cpp
 * @author Jan Wielgus
 * @date 2020-11-11
 * 
 */

#include "../NavigationSystem/VirtualPilot.h"
#include "../Instances/MainInstances.h"
#include "../Instances/MotorsInstance.h"
#include "../Communication/CommData.h"
#include <ArrayIterator.h>

using Enums::FlightModeTypes;
using SimpleDataStructures::ArrayIterator;
using Common::ControlSticks;


VirtualPilot::VirtualPilot(FlightMode& initialFlightMode)
{
    this->currentFlightMode = &initialFlightMode;
}


bool VirtualPilot::addFlightMode(FlightMode* flightMode)
{
    ArrayIterator<FlightMode*> iter(flightModesArray);
    while (iter.hasNext())
        if (iter.next()->getType() == flightMode->getType())
            return false; // flight mode instance of this type was already added

    flightModesArray.add(flightMode);
    return true;
}


bool VirtualPilot::initializeFlightModes()
{
    bool result = true;
    ArrayIterator<FlightMode*> iter(flightModesArray);
    while (iter.hasNext())
        result = result && iter.next()->initializeFlightMode();

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
    Instance::motors.updatePower(virtualSticks);
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
    ArrayIterator<FlightMode*> iter(flightModesArray);
    while (iter.hasNext())
    {
        FlightMode* temp = iter.next();
        if (temp->getType() == flightModeType)
            return temp;
    }

    return nullptr;
}


void VirtualPilot::executePrepareAndLeaveMethods(const FlightMode* oldFlightMode, const FlightMode* newFlightMode)
{
    ArrayIterator<FlightMode*> iter(flightModesArray);
    while (iter.hasNext())
    {
        FlightMode* checked = iter.next();
        bool wasUsed = oldFlightMode->checkIfSuperiorOrEqualOf(checked);
        bool willBeUsed = newFlightMode->checkIfSuperiorOrEqualOf(checked);

        if (!wasUsed && willBeUsed)
            checked->prepare();
        else if (wasUsed && !willBeUsed)
            checked->leave();
    }
}

