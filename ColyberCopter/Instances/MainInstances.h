/**
 * @file MainInstances.h
 * @author Jan Wielgus
 * @brief Contans references to all most important instances
 * that can be used to change drone state or trigger an action.
 * @date 2020-12-01
 * 
 */

#ifndef MAININSTANCES_H
#define MAININSTANCES_H

// TODO: set the order of include files
#include <SimpleTasker.h>
#include "../Interfaces/IAHRS.h"
#include "../Interfaces/ISensorsData.h"
#include "../Interfaces/IVirtualPilot.h"
#include <PacketCommunication.h>
#include "../Sensors/Sensor.h"
#include "../Failsafe/Failsafe.h"
#include "../Debug/DebugMessenger.h"

namespace Instance
{
    using namespace Interfaces;

    extern ITasker& tasker;
    extern IAHRS& ahrs;
    extern ISensorsData& sensorsData;
    extern IVirtualPilot& virtualPilot;
    
    extern PacketCommunication& pilotPacketComm;

    extern Failsafe& failsafe;
    extern DebugMessenger& debMes;
}


#endif

