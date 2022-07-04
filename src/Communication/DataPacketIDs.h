/**
 * @file DataPacketIDs.h
 * @author Jan Wielgus
 * @brief This file contains IDs for all DataPackets used by drone.
 * @date 2022-07-04
 */

#ifndef DATAPACKETSIDS_h
#define DATAPACKETSIDS_h

#include <cstdint>


namespace DataPacketIDs {
    #define PacketIDType constexpr inline uint16_t

    // -------
    // Remember that each data packet should have different ID!
    // -------

    PacketIDType steering               = 0;
    PacketIDType flightModeChange       = 1;
    PacketIDType pidTuning              = 2;
    PacketIDType droneMeasurements      = 50;
    PacketIDType droneState             = 51;

    // all packets IDs have to be created here with the name of data packet itself
    #undef PacketIDType
}


#endif
