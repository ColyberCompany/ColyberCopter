/**
 * @file CopterSetup.h
 * @author  Jan Wielgus
 * @brief Interface for setting up the drone.
 * @date 2020-11-27
 * 
 */

#ifndef COPTERSETUP_H
#define COPTERSETUP_H

#include <SimpleTasker.h>
#include "Interfaces/I3DPosition.h"
#include "Interfaces/I3DRotation.h"
#include "Interfaces/IMotors.h"
#include "Interfaces/ISensorsData.h"
#include "Interfaces/IVirtualPilot.h"
#include <PacketCommunication.h>

#define Serial Serial1


extern SimpleTasker simpleTasker;
//extern PacketCommunication& remoteCtrlPacketComm;
//extern Interfaces::I3DPosition* 3DPosition;


void setupDrone();


#endif

