/**
 * @file PacketReceivedEvents.cpp
 * @author Jan Wielgus
 * @date 2020-12-01
 * 
 */

#include "../Communication/PacketReceivedEvents.h"
#include "../Instances.h"


void SteeringReceivedEvent::execute()
{
    // VirtualPilot get data directly from received variables.

    // Add other actions here if needed.
}


void FlightModeChangeReceivedEvent::execute()
{
    uint8_t newFlightModeType = Instance::pilotPacketsAndData.receiving.data.flightMode;
    Instance::virtualPilot.setFlightMode((Enums::FlightModeTypes)newFlightModeType);
}


// ... (implementations of other received events)

