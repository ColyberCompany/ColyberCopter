/**
 * @file RemoteControlComm.h
 * @author Jan Wielgus
 * @brief This (Singleton) class is used to communicate with remote controller.
 * Way of communication could be changed here. This class also contains 
 * variables that store received data or variables where sent data should be placed.
 * // TODO: maybe write something more after implementing this class.
 * @date 2020-11-09
 * 
 */

#ifndef REMOTECONTROLCOMM_H
#define REMOTECONTROLCOMM_H

#include <StreamComm.h>
#include <PacketCommunicationWithQueue.h>
#include <DataPacket.h>
#include "ReceiveData.h"
#include "SendData.h"


/**
 * @brief Remote Controller Communication
 * (communication with the remote controller).
 */
class RemoteControlComm
{
public:
    RemoteControlComm(PacketCommunication& packetCommunication)
        : comm(packetCommunication),
        // dataPacket(ID):
        steering(0),
        measurementsAndState(10)
    {
    // receive:

        // steering
        steering.addByteType(receiveData.throttle);
        steering.addByteType(receiveData.yaw);
        steering.addByteType(receiveData.pitch);
        steering.addByteType(receiveData.roll);


    // send:

        // measurements and state
        // TODO: think about structure of this packet and if to split it
        measurementsAndState.addByteType(sendData.pitchAngle_deg);
        measurementsAndState.addByteType(sendData.rollAngle_deg);
        measurementsAndState.addByteType(sendData.heading_deg);
        measurementsAndState.addByteType(sendData.altitude_cm);
        measurementsAndState.addByteType(sendData.longitude);
        measurementsAndState.addByteType(sendData.latitude);
        measurementsAndState.addByteType(sendData.droneConnectionStability);
    }


    RemoteControlComm(const RemoteControlComm&) = delete;
    RemoteControlComm& operator=(const RemoteControlComm&) = delete;


private:
    PacketCommunication& comm; // PacketCommunication

public:
    DataForRemoteControl sendData;
    DataFromRemoteControl receiveData;


    // receive data packets
    DataPacket steering; // ID 0
    // add other here

    // send data packets
    DataPacket measurementsAndState; // ID 10
    // add other here

    // TODO: remember to make somewhere receive events and add them to receive packets (outside this class)
};


#endif

