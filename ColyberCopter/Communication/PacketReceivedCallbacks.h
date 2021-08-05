/**
 * @file PacketReceivedCallbacks.h
 * @author Jan Wielgus
 * @brief This file contains definitions of packet received callbacks.
 * @date 2020-12-01
 * 
 */

#ifndef PACKETRECEIVEDCALLBACKS_H
#define PACKETRECEIVEDCALLBACKS_H


namespace PacketReceivedCallbacks
{
    void steeringCallback();
    void flightModeChangeCallback();
    void pidTuningCallback();

    // callbacks for other data packets...
}


#endif
