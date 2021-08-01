/**
 * @file PacketReceivedEvents.cpp
 * @author Jan Wielgus
 * @date 2020-12-01
 * 
 */

#include "../Communication/PacketReceivedCallbacks.h"
#include "../Communication/CommData.h"
#include "../Instances/MainInstances.h"
#include "../Instances/FlightModeInstances.h"

using namespace PacketReceivedCallbacks;


void steeringCallback()
{
    // VirtualPilot get data directly from received variables.

    // Add other actions here if needed.
}


void flightModeChangeCallback()
{
    uint8_t newFlightModeType = commData.flightMode;
    Instance::virtualPilot.setFlightMode((Enums::FlightModeTypes)newFlightModeType);
}


void pidTuningCallback()
{
    using Assemble::FlightModes::stabilizeFlightMode;
    using Instance::debMes;

    debMes.showMessage("Got new PID. ID:");
    debMes.showMessage(commData.pidTuning.tunedController_ID);
    debMes.showMessage("kP, kI, kD, iMax:");
    debMes.showMessage(commData.pidTuning.kP * 100);
    debMes.showMessage(commData.pidTuning.kI * 100);
    debMes.showMessage(commData.pidTuning.kD * 100);
    debMes.showMessage(commData.pidTuning.iMax);
    

    switch (commData.pidTuning.tunedController_ID)
    {
        case 0: // leveling
            stabilizeFlightMode.setLevelingXPIDGains(commData.pidTuning.kP,
                                                     commData.pidTuning.kI,
                                                     commData.pidTuning.kD,
                                                     commData.pidTuning.iMax);

            stabilizeFlightMode.setLevelingYPIDGains(commData.pidTuning.kP,
                                                     commData.pidTuning.kI,
                                                     commData.pidTuning.kD,
                                                     commData.pidTuning.iMax);
            break;
        
        case 1: // yaw  
            stabilizeFlightMode.setHeadingHoldPIDGains(commData.pidTuning.kP,
                                                       commData.pidTuning.kI,
                                                       commData.pidTuning.kD,
                                                       commData.pidTuning.iMax);
    }
}


// ... (implementations of other received events)

