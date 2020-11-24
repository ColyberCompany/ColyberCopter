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


StabilizeFlightMode::StabilizeFlightMode(I3DRotation& rotationData, float deltaTime)
    : FlightMode(FlightModeTypes::STABILIZE, nullptr, deltaTime),
    levelingXPID(deltaTime),
    levelingYPID(deltaTime),
    headingHoldPID(deltaTime),
    rotationData(rotationData)
{
    headingToHold = 0;
    headingError = 0;
}


void StabilizeFlightMode::setLevelingXPIDGains(float kP, float kI, float kD, uint16_t Imax)
{
    levelingXPID.setGains(kP, kI, kD, Imax);
}


void StabilizeFlightMode::setLevelingYPIDGains(float kP, float kI, float kD, uint16_t Imax)
{
    levelingYPID.setGains(kP, kI, kD, Imax);
}


void StabilizeFlightMode::setHeadingHoldPIDGains(float kP, float kI, float kD, uint16_t Imax)
{
    headingHoldPID.setGains(kP, kI, kD, Imax);
}


void StabilizeFlightMode::leave()
{
    resetSticks();

    levelingXPID.reset();
    levelingYPID.reset();
    headingHoldPID.reset();
}


void StabilizeFlightMode::prepare()
{
    setHeadingToHoldToCurrentReading();
}


void StabilizeFlightMode::flightModeLoop()
{
    // TODO: update leveling and heading only if throttle is big enough !!
    updateLeveling();
    updateHeadingHolding();
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
