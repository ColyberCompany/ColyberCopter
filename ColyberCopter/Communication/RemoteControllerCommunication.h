/**
 * @file RemoteControllerCommunication.h
 * @author Jan Wielgus
 * @brief This (Singleton) class is used to communicate with remote controller.
 * Way of communication could be changed here. This class also contains 
 * variables that store received data or variables where sent data should be placed.
 * // TODO: maybe write something more after implementing this class.
 * @date 2020-11-09
 * 
 */

#ifndef REMOTECONTROLLERCOMMUNICATION_H
#define REMOTECONTROLLERCOMMUNICATION_H

#include <StreamComm.h>
#include <PacketCommunicationWithQueue.h>
#include <DataPacket.h>
#include "ReceiveData.h"
#include "SendData.h"
#include "config.h"


class RemoteControllerCommunication
{
// Singleton
private:
    RemoteControllerCommunication();
    RemoteControllerCommunication& instance = RemoteControllerCommunication();
public:
    RemoteControllerCommunication& getInstance()
    {
        return instance;
    }


private:
    ITransceiver& lowLevelComm = StreamComm(&Config::RmtCtrlSerial, Config::RmtCtrlMaxComBufferSize);

public:
    PacketCommunication& comm = PacketCommunicationWithQueue(&lowLevelComm, Config::RmtCtrlMaxQueuedBuffers);
    DataForRmtCtrl sendData;
    DataFromRmtCtrl receiveData;


    // receive data packets
    DataPacket steering = DataPacket(0);
    // add other here

    // send data packets
    DataPacket measurementsAndState = DataPacket(10);
    // add other here

    // TODO: remember to make somewhere receive events and add them to receive packets (outside this class)
};


#endif

