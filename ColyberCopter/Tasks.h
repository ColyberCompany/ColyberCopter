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
            commData.drone.pitchAngle_deg = angles.x;
            commData.drone.rollAngle_deg = angles.y;
            commData.drone.heading_deg = angles.z;
            commData.drone.altitude_cm = Instance::ins.getAltitude_m();
            commData.drone.longitude = Instance::ins.getLongitude_deg();
            commData.drone.latitude = Instance::ins.getLatitude_deg();
            commData.drone.connectionStability = Instance::pilotPacketComm.getConnectionStability();

            Instance::pilotPacketComm.send(&DataPackets::droneMeasurementsAndState);
        }
    } rmtCtrlSendingDroneData;
    


    // add other tasks here
}


#endif
