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
#include <DataPacket.h>
#include <EventPacket.h>


namespace DataPackets
{
    extern PacketComm::DataPacket steering;
    extern PacketComm::DataPacket flightModeChange;
    extern PacketComm::DataPacket droneMeasurementsAndState;
    extern PacketComm::DataPacket pidTuning;
}


#endif
