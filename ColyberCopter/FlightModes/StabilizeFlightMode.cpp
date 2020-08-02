/**
 * @file StabilizeFlightMode.cpp
 * @author Jan Wielgus
 * @date 2020-08-02
 * 
 */

#include "StabilizeFlightMode.h"

using Interfaces::IVirtualPilot;
using Interfaces::I3DRotation;
using Enums::FlightModeTypes;


StabilizeFlightMode::StabilizeFlightMode(IVirtualPilot* virtualPilot,
        PID* levelingX_PID, PID* levelingY_PID, PID* headingHold_PID,
        I3DRotation* rotationDataPtr, float deltaTime)
    : FlightMode(FlightModeTypes::STABILIZE, nullptr, virtualPilot),
    levelingXPID(*levelingX_PID),
    levelingYPID(*levelingY_PID),
    headingHoldPID(*headingHold_PID),
    rotationData(*rotationDataPtr)
{
    this->deltaTime = deltaTime;

    headingToHold = 0;
}


void StabilizeFlightMode::idleLoop()
{
    resetSticks();
    setHeadingToHoldToCurrentReading();

    runBaseFlightModeIdleLoop(); // remember in other flight modes
}


void StabilizeFlightMode::run()
{
    updateLeveling();
    updateHeadingHolding();

    // runBaseFlightMode(); - not needed there, but remember in other flight modes
}


void StabilizeFlightMode::prepare()
{
    setHeadingToHoldToCurrentReading();
}


void StabilizeFlightMode::leave()
{
    resetSticks();

    levelingXPID.reset();
    levelingYPID.reset();
    headingHoldPID.reset();
}


void StabilizeFlightMode::updateLeveling()
{
    virtualSticks.setTB(levelingXPID.update(virtualSticks.getTB() / 10.f, rotationData.getPitch_deg()) + 0.5f);
    virtualSticks.setLR(levelingYPID.update(virtualSticks.getLR() / 10.f, rotationData.getRoll_deg()) + 0.5f);
}


void StabilizeFlightMode::updateHeadingHolding()
{
    integrateHeadingToHold();

    headingError = headingToHold - rotationData.getHeading_deg();
    if (headingError > 180)
        headingError -= 360;
    else if (headingError < -180)
        headingError += 360;
    
    virtualSticks.setRotation(headingHoldPID.update(headingError));
}


void StabilizeFlightMode::integrateHeadingToHold()
{
    headingToHold += ((float)(virtualSticks.getRotation() / 2.f) * deltaTime);
}


void StabilizeFlightMode::resetSticks()
{
    virtualSticks.setRotation(0);
    virtualSticks.setTB(0);
    virtualSticks.setLR(0);
}


void StabilizeFlightMode::setHeadingToHoldToCurrentReading()
{
    headingToHold = rotationData.getHeading_deg();
}
