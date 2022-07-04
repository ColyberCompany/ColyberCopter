/**
 * @file DataPackets.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief This class contains instances of all data packets.
 * @date 2021-03-28
 */

#ifndef DATAPACKETS_H
#define DATAPACKETS_H

#include "CommData.h"
#include <DataPacket.h>
#include <EventPacket.h>


namespace DataPackets
{
    using PacketComm::DataPacket;

    // received:
    extern DataPacket steering;
    extern DataPacket flightModeChange;
    extern DataPacket pidTuning;
    // sent:
    extern DataPacket droneMeasurements;
    extern DataPacket droneState;
}


#endif
