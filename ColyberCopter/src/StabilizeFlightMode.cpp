/**
 * @file StabilizeFlightMode.cpp
 * @author Jan Wielgus
 * @date 2020-08-02
 * 
 */

#include "../FlightModes/StabilizeFlightMode.h"
#include "../Common/Constants.h"

using Interfaces::IVirtualPilot;
using Interfaces::I3DRotation;
using Enums::FlightModeTypes;
using Consts::RoundAngle;;
using Consts::StraightAngle;


StabilizeFlightMode::StabilizeFlightMode(I3DRotation& rotationData)
    : FlightMode(FlightModeTypes::STABILIZE, nullptr),
    levelingXPID(DeltaTime_s),
    levelingYPID(DeltaTime_s),
    headingHoldPID(DeltaTime_s),
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
    levelingXPID.reset();
    levelingYPID.reset();
    headingHoldPID.reset();
}


void StabilizeFlightMode::prepare()
{
    setHeadingToHoldToCurrentReading();
}


void StabilizeFlightMode::flightModeLoop(ControlSticks& inputOutputSticks)
{
    if (inputOutputSticks.getThrottle() < 100)
        return;

    updateLeveling(inputOutputSticks);
    updateHeadingHolding(inputOutputSticks);
}



void StabilizeFlightMode::updateLeveling(ControlSticks& inputOutputSticks)
{
    inputOutputSticks.setPitch(levelingXPID.update(inputOutputSticks.getPitch() / 10.f, rotationData.getPitch_deg()) + 0.5f);
    inputOutputSticks.setRoll(levelingYPID.update(inputOutputSticks.getRoll() / 10.f, rotationData.getRoll_deg()) + 0.5f);
}


void StabilizeFlightMode::updateHeadingHolding(ControlSticks& inputOutputSticks)
{
    integrateHeadingToHold(inputOutputSticks.getYaw());
    calculateHeadingError();
    inputOutputSticks.setYaw(headingHoldPID.update(headingError));
}


void StabilizeFlightMode::integrateHeadingToHold(int16_t yawStick)
{
    headingToHold += ((float)(yawStick / 2.f) * DeltaTime_s);
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
