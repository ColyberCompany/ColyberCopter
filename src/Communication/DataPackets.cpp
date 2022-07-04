/**
 * @file CommunicationGlobals.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Instantiation of communication data packets.
 * @date 2021-03-28
 */

#include "DataPackets.h"
#include "DataPacketIDs.h"
#include "PacketReceivedCallbacks.h"

#define payload(x) ((uint8_t*)&(x))
#define payloadSize(x) (sizeof(x))

// Better looking way to create a DataPacket instance
#define DATA_PACKET_SENDING(name) \
    PacketComm::DataPacket name(DataPacketIDs::name, payload(commData.name), payloadSize(commData.name))
#define DATA_PACKET_RECEIVING(name, callback) \
    PacketComm::DataPacket name(DataPacketIDs::name, payload(commData.name), payloadSize(commData.name), callback)


CommData commData;


namespace DataPackets
{
    using namespace PacketReceivedCallbacks;

    // received:
    DATA_PACKET_RECEIVING(steering, steeringCallback);
    DATA_PACKET_RECEIVING(flightModeChange, flightModeChangeCallback);
    DATA_PACKET_RECEIVING(pidTuning, pidTuningCallback);
    // sent:
    DATA_PACKET_SENDING(droneMeasurements);
    DATA_PACKET_SENDING(droneState);
}
