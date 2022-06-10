/**
 * @file PacketReceivedEvents.cpp
 * @author Jan Wielgus
 * @date 2020-12-01
 * 
 */

#include "PacketReceivedCallbacks.h"
#include "CommData.h"
#include "Instances/MainInstances.h"
#include "Instances/FlightModeInstances.h"


void PacketReceivedCallbacks::steeringCallback()
{
    // VirtualPilot get data directly from received variables.

    // Add other actions here if needed.
}


void PacketReceivedCallbacks::flightModeChangeCallback()
{
    uint8_t newFlightModeType = commData.flightModeChange.flightMode;
    Instance::virtualPilot.setFlightMode((FlightMode::FlightModeTypes)newFlightModeType);
    // TODO: show result of setting the flight mode in a debug message (maybe show debug message in VirtualPilot)

    // TODO: log flight mode setting result (maybe log flight mode change in VirtualPilot class)
}


void PacketReceivedCallbacks::pidTuningCallback()
{
    using Assemble::FlightModes::stabilizeFlightMode;
    using Assemble::FlightModes::altHoldFlightMode;
    using Instance::debMes;

    auto& data = commData.pidTuning;

    debMes.showMessage("Got new PID. ID:");
    debMes.showMessage(data.tunedController_ID);
    debMes.showMessage("kP, kI, kD, iMax:");
    debMes.showMessage(data.kP * 100);
    debMes.showMessage(data.kI * 100);
    debMes.showMessage(data.kD * 100);
    debMes.showMessage(data.iMax);
    

    switch (data.tunedController_ID)
    {
        case 0: // leveling
            stabilizeFlightMode.setLevelingXPIDGains(
                data.kP,
                data.kI,
                data.kD,
                data.iMax
            );

            stabilizeFlightMode.setLevelingYPIDGains(
                data.kP,
                data.kI,
                data.kD,
                data.iMax
            );
            break;
        
        case 1: // yaw  
            stabilizeFlightMode.setHeadingHoldPIDGains(
                data.kP,
                data.kI,
                data.kD,
                data.iMax
            );
            break;

        case 2: // altHold
            altHoldFlightMode.setAltHoldPIDGains(
                data.kP,
                data.kI,
                data.kD,
                data.iMax
            );
            break;
}
}


// ... (implementations of other received events)

