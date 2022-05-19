/**
 * @file AltHoldFlightMode.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-02-24
 */

#include "AltHoldFlightMode.h"
#include "Instances/MainInstances.h"
#include "config.h"
#include "Common/Constants.h"

using Common::ControlSticks;
using Common::Consts::ThrottleStickCenter;


const uint16_t AltHoldFlightMode::MinOutputThrottle = 300;
const uint16_t AltHoldFlightMode::MaxOutputThrottle = 700;
const uint16_t AltHoldFlightMode::MaxClimbRate_cmPerSec = 100; // also for declining
const uint16_t AltHoldFlightMode::ThrottleDeadZone = 55;

const float AltHoldFlightMode::ThrottleClimbRateMult = (float)MaxClimbRate_cmPerSec / (500.f - ThrottleDeadZone);


AltHoldFlightMode::AltHoldFlightMode(StabilizeFlightMode& stabilizeFlightMode)
    : FlightMode(FlightModeTypes::ALT_HOLD, &stabilizeFlightMode),
    altitudeHoldPID(Config::MainInterval_s)
{
    setAltHoldPIDGains(Config::AltHoldPID_kP,
                       Config::AltHoldPID_kI,
                       Config::AltHoldPID_kD,
                       Config::AltHoldPID_IMax);

    altitudeHoldPID.set_derivCutoffFreq(5.f); // TODO: make this a named constant somewhere
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


const char* AltHoldFlightMode::getName()
{
    return "alt_hold";
}


void AltHoldFlightMode::flightModeLoop(ControlSticks& inputOutputSticks)
{
    updateAltitudeToHold(inputOutputSticks.getThrottle());

    int16_t outputThrottle = altHoldThrottle;
    outputThrottle += altitudeHoldPID.update(altitudeToHold_cm, Instance::ins.getAltitude_m() * 100.f) + 0.5f;
    outputThrottle = constrain(outputThrottle, MinOutputThrottle, MaxOutputThrottle);

    inputOutputSticks.setThrottle(outputThrottle);
}


void AltHoldFlightMode::updateAltitudeToHold(uint16_t throttle)
{
    altitudeToHold_cm += throttleToClimbRate_cmPerSec(throttle) * Config::MainInterval_s;
}


void AltHoldFlightMode::setAltitudeToHoldToCurrentReading()
{
    altitudeToHold_cm = Instance::ins.getAltitude_m() * 100.f;
}


float AltHoldFlightMode::throttleToClimbRate_cmPerSec(uint16_t throttle)
{
    int16_t centeredThrottle = throttle - ThrottleStickCenter;

    if (centeredThrottle > ThrottleDeadZone)
        return (centeredThrottle - ThrottleDeadZone) * ThrottleClimbRateMult;
    else if (centeredThrottle < -ThrottleDeadZone)
        return (centeredThrottle + ThrottleDeadZone) * ThrottleClimbRateMult;
    else
        return 0.f;
}
