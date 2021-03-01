/**
 * @file AltHoldFlightMode.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-02-24
 * 
 */

#include "../FlightModes/AltHoldFlightMode.h"
#include "../config.h"


using Interfaces::IAHRS;
using Enums::FlightModeTypes;


AltHoldFlightMode::AltHoldFlightMode(StabilizeFlightMode& stabilizeFlightMode, IAHRS& _ahrs)
    : FlightMode(FlightModeTypes::ALT_HOLD, &stabilizeFlightMode),
    ahrs(_ahrs),
    altitudeHoldPID(DeltaTime_s)
{
}


void AltHoldFlightMode::setAltHoldPIDGains(float kP, float kI, float kD, uint16_t Imax)
{
    altitudeHoldPID.setGains(kP, kI, kD, Imax);
}


void AltHoldFlightMode::leave()
{
    altitudeHoldPID.reset();
}


void AltHoldFlightMode::prepare()
{
    setAltitudeToHoldToCurrentReading();
}


void AltHoldFlightMode::flightModeLoop(ControlSticks& inputOutputSticks)
{
    if (inputOutputSticks.getThrottle() < 80) // TODO: think if this could be checked in a better way then just throttle threshold
        return;
    
    updateAltitudeHolding(inputOutputSticks);
}


void AltHoldFlightMode::updateAltitudeHolding(ControlSticks& inputOutputSticks)
{
    updateAltitudeToHold(inputOutputSticks.getThrottle());
    calculateAltitudeError();

    int16_t outputThrottle = altitudeHoldPID.update(altitudeError_cm);
    outputThrottle = constrain(outputThrottle, MinOutputThrottle, MaxOutputThrottle);
    inputOutputSticks.setThrottle(outputThrottle);
}


void AltHoldFlightMode::updateAltitudeToHold(uint16_t throttle)
{
    altitudeToHold_cm += climbRateFromThr_cmPerSec(throttle) * DeltaTime_s;
}


void AltHoldFlightMode::calculateAltitudeError()
{
    altitudeError_cm = altitudeToHold_cm - (ahrs.getAltitude_m() * 100.f);
}


void AltHoldFlightMode::setAltitudeToHoldToCurrentReading()
{
    altitudeToHold_cm = ahrs.getAltitude_m() * 100.f;
}


float AltHoldFlightMode::climbRateFromThr_cmPerSec(uint16_t throttle)
{
    int16_t centeredThrottle = throttle - Config::ThrottleStickCenter;
    return centeredThrottle * ThrottleMultiplier;
}
