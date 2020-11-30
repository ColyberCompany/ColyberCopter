/**
 * @file RmtCtrlCommunication.h
 * @author Jan Wielgus
 * @brief This (Singleton) class is used to communicate with remote controller.
 * Way of communication could be changed here. This class also contains 
 * variables that store received data or variables where sent data should be placed.
 * // TODO: maybe write something more after implementing this class.
 * @date 2020-11-09
 * 
 */

#ifndef RMTCTRLCOMMUNICATION_H
#define RMTCTRLCOMMUNICATION_H

#include <StreamComm.h>
#include <PacketCommunicationWithQueue.h>
#include <DataPacket.h>
#include "ReceiveData.h"
#include "SendData.h"


/**
 * @brief Remote Controller Communication
 * (communication with the remote controller).
 */
class RmtCtrlCommunication
{
public:
    RmtCtrlCommunication(PacketCommunication& packetCommunication);
    // TODO: delete copy ctor and = operator

private:
    PacketCommunication& comm; // PacketCommunication

public:
    DataForRmtCtrl sendData;
    DataFromRmtCtrl receiveData;


    // receive data packets
    DataPacket steering; // ID 0
    // add other here

    // send data packets
    DataPacket measurementsAndState; // ID 10
    // add other here

    // TODO: remember to make somewhere receive events and add them to receive packets (outside this class)
};


#endif

