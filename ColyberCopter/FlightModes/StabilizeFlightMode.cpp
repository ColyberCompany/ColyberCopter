/**
 * @file StabilizeFlightMode.cpp
 * @author Jan Wielgus
 * @date 2020-08-02
 * 
 */

#include "StabilizeFlightMode.h"
#include "Common/Constants.h"

using Interfaces::IVirtualPilot;
using Interfaces::I3DRotation;
using Enums::FlightModeTypes;
using Consts::RoundAngle;;
using Consts::StraightAngle;


StabilizeFlightMode::StabilizeFlightMode(PID& levelingX_PID, PID& levelingY_PID, PID& headingHold_PID,
        I3DRotation& rotationData, float deltaTime)
    : FlightMode(FlightModeTypes::STABILIZE, nullptr, deltaTime),
    levelingXPID(levelingX_PID),
    levelingYPID(levelingY_PID),
    headingHoldPID(headingHold_PID),
    rotationData(rotationData)
{
    headingToHold = 0;
    headingError = 0;
}


void StabilizeFlightMode::disarmedLoop()
{
    runBaseFlightModeDisarmedLoop(); // remember in other flight modes
}


void StabilizeFlightMode::armedLoop()
{
    updateLeveling();
    updateHeadingHolding();

    // runBaseFlightModeArmedLoop(); - not needed there, but remember in other flight modes
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
    virtualSticks.setPitch(levelingXPID.update(virtualSticks.getPitch() / 10.f, rotationData.getPitch_deg()) + 0.5f);
    virtualSticks.setRoll(levelingYPID.update(virtualSticks.getRoll() / 10.f, rotationData.getRoll_deg()) + 0.5f);
}


void StabilizeFlightMode::updateHeadingHolding()
{
    integrateHeadingToHold();
    calculateHeadingError();
    virtualSticks.setYaw(headingHoldPID.update(headingError));
}


void StabilizeFlightMode::integrateHeadingToHold()
{
    headingToHold += ((float)(virtualSticks.getYaw() / 2.f) * DeltaTime);
    headingToHold = correctHeading(headingToHold);
}


void StabilizeFlightMode::calculateHeadingError()
{
    headingError = headingToHold - rotationData.getHeading_deg();

    if (headingError > StraightAngle)
        headingError -= RoundAngle;
    else if (headingError < -StraightAngle)
        headingError += RoundAngle;
}


void StabilizeFlightMode::setHeadingToHoldToCurrentReading()
{
    headingToHold = rotationData.getHeading_deg();
}


float StabilizeFlightMode::correctHeading(float headingToCorrect)
{
    if (headingToCorrect >= RoundAngle)
    {
        headingToCorrect -= RoundAngle;
        while (headingToCorrect >= RoundAngle)
            headingToCorrect -= RoundAngle;
    }
    else if (headingToCorrect < 0.f)
    {
        headingToCorrect += RoundAngle;
        while (headingToCorrect < 0.f)
            headingToCorrect += RoundAngle;
    }
    
    return headingToCorrect;
}
