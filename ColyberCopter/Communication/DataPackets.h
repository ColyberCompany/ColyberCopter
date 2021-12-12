/**
 * @file DataPackets.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief This class contains instances of all data packets.
 * @date 2021-03-28
 * 
 */

#ifndef DATAPACKETS_H
#define DATAPACKETS_H

#include "CommData.h"
#include "PacketReceivedCallbacks.h"
#include <DataPacket.h>
#include <EventPacket.h>

// -------
// Remember that each data packet should have different ID!
// -------


namespace DataPacketClasses
{
    class Steering : public PacketComm::DataPacket
    {
    public:
        Steering()
            : DataPacket(0)
        {
            addVar(commData.pilot.stick.throttle);
            addVar(commData.pilot.stick.yaw);
            addVar(commData.pilot.stick.pitch);
            addVar(commData.pilot.stick.roll);

            setOnReceiveCallback(PacketReceivedCallbacks::steeringCallback);
        }
    };


    class FlightModeChange : public PacketComm::DataPacket
    {
    public:
        FlightModeChange()
            : DataPacket(10)
        {
            addVar(commData.flightMode);

            setOnReceiveCallback(PacketReceivedCallbacks::flightModeChangeCallback);
        }
    };


    class DroneMeasurementsAndState : public PacketComm::DataPacket
    {
    public:
        DroneMeasurementsAndState()
            : DataPacket(50)
        {
            addVar(commData.drone.pitchAngle_deg);
            addVar(commData.drone.rollAngle_deg);
            addVar(commData.drone.heading_deg);
            addVar(commData.drone.altitude_cm);
            addVar(commData.drone.longitude);
            addVar(commData.drone.latitude);
            addVar(commData.drone.connectionStability);

            addVar(commData.drone.pitch);
            addVar(commData.drone.roll);
            addVar(commData.drone.accX);
            addVar(commData.drone.accY);
            addVar(commData.drone.accZ);
            addVar(commData.drone.gyroX);
            addVar(commData.drone.gyroY);
            addVar(commData.drone.gyroZ);
            addVar(commData.drone.magnX);
            addVar(commData.drone.magnY);
            addVar(commData.drone.magnZ);
        }
    };


    class PIDTuning : public PacketComm::DataPacket
    {
    public:
        PIDTuning()
            : DataPacket(51)
        {
            addVar(commData.pidTuning.tunedController_ID);
            addVar(commData.pidTuning.kP);
            addVar(commData.pidTuning.kI);
            addVar(commData.pidTuning.kD);
            addVar(commData.pidTuning.iMax);

            setOnReceiveCallback(PacketReceivedCallbacks::pidTuningCallback);
        }
    };
}


namespace DataPackets
{
    // Instances created in src/CommunicationGlobals.cpp
    extern DataPacketClasses::Steering steering;
    extern DataPacketClasses::FlightModeChange flightModeChange;
    extern DataPacketClasses::DroneMeasurementsAndState droneMeasurementsAndState;
    extern DataPacketClasses::PIDTuning pidTuning;
}


#endif
