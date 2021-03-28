/**
 * @file PacketReceivedEvents.cpp
 * @author Jan Wielgus
 * @date 2020-12-01
 * 
 */

#include "../Communication/PacketReceivedEvents.h"
#include "../Instances.h"
#include "../Communication/CommData.h"

using namespace PacketReceivedEvents;


void Steering::execute()
{
    // VirtualPilot get data directly from received variables.

    // Add other actions here if needed.
}


void FlightModeChange::execute()
{
    uint8_t newFlightModeType = commData.flightMode;
    Instance::virtualPilot.setFlightMode((Enums::FlightModeTypes)newFlightModeType);
}


void PIDTuning::execute()
{




    // TODO: <<<<<<<<< IMPLEMENT



    // ><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< IMPLEMENT
}


// ... (implementations of other received events)

