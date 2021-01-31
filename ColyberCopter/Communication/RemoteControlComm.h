/**
 * @file RemoteControlComm.h
 * @author Jan Wielgus
 * @brief This class contain all data packets and sending/receiving
 * variables. PacketsIDs are set there.
 * @date 2020-11-09
 * 
 */

#ifndef REMOTECONTROLCOMM_H
#define REMOTECONTROLCOMM_H

#include <StreamComm.h>
#include <PacketCommunication.h>
#include <DataPacket.h>
#include "ReceiveData.h"
#include "SendData.h"
#include "PacketReceivedEvents.h"


/**
 * @brief Remote Controller Communication
 * (communication with the remote controller).
 */
class RemoteControlComm
{
public:
    struct Sending
    {
        DataForRemoteControl data;

        DataPacket measurementsAndState;
        // add other here ...

        Sending()
            : measurementsAndState(10)
        {}
    } sending;


    struct Receiving
    {
        DataFromRemoteControl data;

        DataPacket steering;
        DataPacket flightModeChange;
        // add other here ...

        Receiving()
            : steering(0),
              flightModeChange(10)
        {}
    } receiving;
    

private:
    SteeringReceivedEvent steeringReceivedEvent;




public:
    RemoteControlComm(PacketCommunication& packetComm)
    {
        // - add all data that this packet consists of
        // - set packet received events for received packets
        // - add receive data packets pointers to the packetComm

    // receive:

        // steering
        receiving.steering.addByteType(receiving.data.throttle);
        receiving.steering.addByteType(receiving.data.yaw);
        receiving.steering.addByteType(receiving.data.pitch);
        receiving.steering.addByteType(receiving.data.roll);
        receiving.steering.setPacketReceivedEvent(steeringReceivedEvent);

        // flight mode change
        receiving.flightModeChange.addByteType(receiving.data.flightMode);

        // Add all receiving packets to the PacketCommunication instance!! <<<<<<<<<<
        packetComm.addReceiveDataPacketPointer(&receiving.steering);
        packetComm.addReceiveDataPacketPointer(&receiving.flightModeChange);


    // send:

        // measurements and state
        // TODO: think about structure of this packet and if to split it
        sending.measurementsAndState.addByteType(sending.data.pitchAngle_deg);
        sending.measurementsAndState.addByteType(sending.data.rollAngle_deg);
        sending.measurementsAndState.addByteType(sending.data.heading_deg);
        sending.measurementsAndState.addByteType(sending.data.altitude_cm);
        sending.measurementsAndState.addByteType(sending.data.longitude);
        sending.measurementsAndState.addByteType(sending.data.latitude);
        sending.measurementsAndState.addByteType(sending.data.droneConnectionStability);

    }


    RemoteControlComm(const RemoteControlComm&) = delete;
    RemoteControlComm& operator=(const RemoteControlComm&) = delete;
};


#endif

