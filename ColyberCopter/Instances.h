/**
 * @file Instances.h
 * @author Jan Wielgus
 * @brief Contans references to all most important instances
 * that can be used to change drone state or trigger an action.
 * @date 2020-12-01
 * 
 */

#ifndef INSTANCES_H
#define INSTANCES_H

// TODO: set the order of include files
#include <SimpleTasker.h>
#include "Interfaces/IAHRS.h"
#include "Interfaces/IMotors.h"
#include "Interfaces/ISensorsData.h"
#include "Interfaces/IVirtualPilot.h"
#include <PacketCommunication.h>
#include "Sensors/Sensor.h"
#include "Failsafe/Failsafe.h"
#include "Debug/DebugMessenger.h"

namespace Instance
{
    using namespace Interfaces;

    extern ITasker& tasker;
    extern IAHRS& ahrs;
    //extern IMotors& motors; // for safety
    extern ISensorsData& sensorsData;
    extern IVirtualPilot& virtualPilot;
    
    extern PacketCommunication& pilotPacketComm;

    extern Sensor& accel;
    extern Sensor& gyro;
    extern Sensor& magn;
    extern Sensor& baro;
    extern Sensor& gps;
    extern Sensor& btmRangefinder;

    extern Failsafe& failsafe;
    extern DebugMessenger& debMes;
}


#endif

