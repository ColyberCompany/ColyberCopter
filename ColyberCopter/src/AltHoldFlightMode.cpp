/**
 * @file AltHoldFlightMode.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-02-24
 * 
 */

#include "../FlightModes/AltHoldFlightMode.h"


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
    //if (inputOutputSticks.getThrottle() < 100)
}


void AltHoldFlightMode::setAltitudeToHoldToCurrentReading()
{
    altitudeToHold = ahrs.getAltitude_m();
}


void AltHoldFlightMode::updateAltitudeToHold(uint16_t throttle)
{

}


void AltHoldFlightMode::calculateAltitudeError()
{
    altitudeError = altitudeToHold - ahrs.getAltitude_m();
}
