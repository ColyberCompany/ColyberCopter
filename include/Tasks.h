/**
 * @file Tasks.h
 * @author Jan Wielgus
 * @brief List of all tasks and executables.
 * @date 2021-01-05
 * 
 */

#ifndef TASKS_H
#define TASKS_H

#include <IExecutable.h>
#include "Instances/MainInstances.h" // Exemption: this header file can include Instances, because only CopterSetup.h includes this file.
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"


namespace Tasks
{
    class : public IExecutable
    {
        bool lastLedState = false;
        void execute() override {
            lastLedState = !lastLedState;
            digitalWrite(LED_BUILTIN, lastLedState);
        }
    } builtinDiodeBlink;



    class : public IExecutable
    {
        void execute() override {
            Instance::pilotPacketComm.receive();
        }
    } rmtCtrlReceiving;



    class : public IExecutable
    {
        void execute() override
        {
            auto angles = Instance::ins.getAngles_deg();

            auto& data = commData.droneMeasurements;
            data.anglePitch = angles.x * 100;
            data.angleRoll = angles.y * 100;
            data.heading = angles.z;
            data.altitude = Instance::ins.getAltitude_m();
            data.longitude = Instance::ins.getLongitude_deg();
            data.latitude = Instance::ins.getLatitude_deg();
            Instance::pilotPacketComm.send(&DataPackets::droneMeasurements);

            auto& data2 = commData.droneState;
            data2.connectionStability = Instance::pilotPacketComm.getConnectionStability();
            Instance::pilotPacketComm.send(&DataPackets::droneState);
        }
    } rmtCtrlSendingDroneData;
    


    // add other tasks here
}


#endif
