/**
 * @file StabilizeFlightMode.cpp
 * @author Jan Wielgus
 * @date 2020-08-02
 * 
 */

#include "StabilizeFlightMode.h"
#include "Common/ControlSticks.h"
#include "Common/Constants.h"
#include "Instances/MainInstances.h"
#include "config.h"
#include <cmath>

using Common::Consts::RoundAngle;
using Common::Consts::StraightAngle;
using Common::ControlSticks;
using Common::vector3Float;

using Config::LevelingPID_kP;
using Config::LevelingPID_kI;
using Config::LevelingPID_kD;
using Config::LevelingPID_IMax;
using Config::HeadHoldPID_kP;
using Config::HeadHoldPID_kI;
using Config::HeadHoldPID_kD;
using Config::HeadHoldPID_IMax;


StabilizeFlightMode::StabilizeFlightMode()
    : FlightMode(FlightModeTypes::STABILIZE, nullptr),
    levelingXPID(Config::MainInterval_s),
    levelingYPID(Config::MainInterval_s),
    headingHoldPID(Config::MainInterval_s)
{
    levelingXPID.setGains(LevelingPID_kP, LevelingPID_kI, LevelingPID_kD, LevelingPID_IMax);
    levelingYPID.setGains(LevelingPID_kP, LevelingPID_kI, LevelingPID_kD, LevelingPID_IMax);
    headingHoldPID.setGains(HeadHoldPID_kP, HeadHoldPID_kI, HeadHoldPID_kD, HeadHoldPID_IMax);

    // TODO: setup D low-pass filters
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


const char* StabilizeFlightMode::getName()
{
    return "stabilize";
}


void StabilizeFlightMode::flightModeLoop(ControlSticks& inputOutputSticks)
{
    if (inputOutputSticks.getThrottle() < 100) // TODO: think if this could be checked in a better way then just throttle threshold
        return;

    throttleTiltCompensation(inputOutputSticks);
    updateLeveling(inputOutputSticks);
    updateHeadingHolding(inputOutputSticks);
}


void StabilizeFlightMode::throttleTiltCompensation(Common::ControlSticks& inputOutputSticks)
{
    vector3Float angles_rad = Instance::ins.getAngles_rad();
    float tiltCompThrMult = 1.f / ( cosf(angles_rad.x) * cosf(angles_rad.y) ); // tilt compensation throttle multiplier
    if (tiltCompThrMult > Config::MaxTiltCompThrMult)
        tiltCompThrMult = Config::MaxTiltCompThrMult;

    float throttle = (float)inputOutputSticks.getThrottle();
    inputOutputSticks.setThrottle(throttle * tiltCompThrMult);
}


void StabilizeFlightMode::updateLeveling(ControlSticks& inputOutputSticks)
{
    float finalPitch = stickToAngle(inputOutputSticks.getPitch());
    float finalRoll = stickToAngle(inputOutputSticks.getRoll());
    vector3Float angles = Instance::ins.getAngles_deg();

    inputOutputSticks.setPitch(levelingXPID.update(finalPitch, angles.x) + 0.5f);
    inputOutputSticks.setRoll(levelingYPID.update(finalRoll, angles.y) + 0.5f);
}


void StabilizeFlightMode::updateHeadingHolding(ControlSticks& inputOutputSticks)
{
    updateHeadingToHold(inputOutputSticks.getYaw());
    calculateHeadingError();
    
    inputOutputSticks.setYaw(headingHoldPID.update(headingError));
}


void StabilizeFlightMode::updateHeadingToHold(int16_t yawStick)
{
    headingToHold -= ((float)(yawStick / 2.f) * Config::MainInterval_s);
    headingToHold = correctHeading(headingToHold);
}


void StabilizeFlightMode::calculateHeadingError()
{
    headingError = headingToHold - Instance::ins.getHeading_deg();

    if (headingError > StraightAngle)
        headingError -= RoundAngle;
    else if (headingError < -StraightAngle)
        headingError += RoundAngle;
}


void StabilizeFlightMode::setHeadingToHoldToCurrentReading()
{
    headingToHold = Instance::ins.getHeading_deg();
}


float StabilizeFlightMode::correctHeading(float headingToCorrect)
{
    while (headingToCorrect >= RoundAngle)
        headingToCorrect -= RoundAngle;
        
    while (headingToCorrect < 0.f)
        headingToCorrect += RoundAngle;
    
    return headingToCorrect;
}


constexpr float StabilizeFlightMode::stickToAngle(int16_t stickValue)
{
    return stickValue * (Config::StabilizeMaxTiltAngle_deg / ControlSticks::MaxPitchRollYaw); // stickValue * (MaxTiltAngle / MaxStickValue)
}
