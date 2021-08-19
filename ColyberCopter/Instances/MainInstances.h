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

#include "../Interfaces/IAHRS.h"
#include "../Interfaces/IVirtualPilot.h"
#include "../Failsafe/FailsafeManager.h"
#include "../Debug/DebugMessenger.h"
#include "../Logger/Logger.h"
#include <Tasker.h>
#include <PacketCommunication.h>

namespace Instance
{
    using namespace Interfaces;

    extern Tasker& tasker;
    extern IAHRS& ahrs;
    extern IVirtualPilot& virtualPilot;
    
    extern PacketComm::PacketCommunication& pilotPacketComm;

    extern FailsafeManager& failsafeManager;
    extern DebugMessenger& debMes;
    extern Logger& logger;
}


#endif

