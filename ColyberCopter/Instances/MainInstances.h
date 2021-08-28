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
#include <Tasker.h>
#include "../NavigationSystem/INS.h"
#include "../Interfaces/IVirtualPilot.h"
#include <PacketCommunication.h>
#include "../Failsafe/FailsafeManager.h"
#include "../Debug/DebugMessenger.h"

namespace Instance
{
    using namespace Interfaces;

    extern Tasker& tasker;
    extern INS& ins;
    extern IVirtualPilot& virtualPilot;
    
    extern PacketComm::PacketCommunication& pilotPacketComm;

    extern FailsafeManager& failsafeManager;
    extern DebugMessenger& debMes;
}


#endif

