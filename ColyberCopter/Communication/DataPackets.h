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
#include "PacketReceivedEvents.h"
#include <DataPacket.h>
#include <EventPacket.h>

// -------
// Remember that each data packet should have different ID!
// -------


namespace DataPacketClasses
{
    class Steering : public DataPacket
    {
        PacketReceivedEvents::Steering recEvent;

    public:
        Steering() : DataPacket(0) {
            addByteType(commData.pilot.stick.throttle);
            addByteType(commData.pilot.stick.yaw);
            addByteType(commData.pilot.stick.pitch);
            addByteType(commData.pilot.stick.roll);

            setPacketReceivedEvent(recEvent);
        }
    };


    class FlightModeChange : public DataPacket
    {
        PacketReceivedEvents::FlightModeChange recEvent;

    public:
        FlightModeChange() : DataPacket(10) {
            addByteType(commData.flightMode);

            setPacketReceivedEvent(recEvent);
        }
    };


    class DroneMeasurementsAndState : public DataPacket
    {
    public:
        DroneMeasurementsAndState() : DataPacket(50) {
            addByteType(commData.drone.pitchAngle_deg);
            addByteType(commData.drone.rollAngle_deg);
            addByteType(commData.drone.heading_deg);
            addByteType(commData.drone.altitude_cm);
            addByteType(commData.drone.longitude);
            addByteType(commData.drone.latitude);
            addByteType(commData.drone.connectionStability);
        }
    };


    class PIDTuning : public DataPacket
    {
        PacketReceivedEvents::PIDTuning recEvent;

    public:
        PIDTuning() : DataPacket(51) {
            addByteType(commData.pidTuning.tunedController_ID);
            addByteType(commData.pidTuning.kP);
            addByteType(commData.pidTuning.kI);
            addByteType(commData.pidTuning.kD);
            addByteType(commData.pidTuning.iMax);

            setPacketReceivedEvent(recEvent);
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
