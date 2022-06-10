/**
 * @file CommunicationGlobals.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Instantiation of communication global variables.
 * @date 2021-03-28
 * 
 */

#include "DataPackets.h"
#include "PacketReceivedCallbacks.h"

#define payload(x) ((uint8_t*)&(x))
#define payloadSize(x) (sizeof(x))


CommData commData;


namespace DataPackets
{
    using PacketComm::DataPacket;
    using namespace PacketReceivedCallbacks;

    // -------
    // Remember that each data packet should have different ID!
    // -------

    DataPacket steering(
        0,
        payload(commData.steering),
        payloadSize(commData.steering),
        steeringCallback
    );

    DataPacket flightModeChange(
        10,
        payload(commData.flightModeChange),
        payloadSize(commData.flightModeChange),
        flightModeChangeCallback
    );

    DataPacket droneMeasurementsAndState(
        50,
        payload(commData.droneMeasurementsAndState),
        payloadSize(commData.droneMeasurementsAndState)
    );

    DataPacket pidTuning(
        51,
        payload(commData.pidTuning),
        payloadSize(commData.pidTuning),
        pidTuningCallback
    );
}
