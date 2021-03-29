/**
 * @file PacketReceivedEvents.h
 * @author Jan Wielgus
 * @brief This file contains definitions of packet received events.
 * @date 2020-12-01
 * 
 */

#ifndef PACKETRECEIVEDEVENTS_H
#define PACKETRECEIVEDEVENTS_H

#include <IExecutable.h>


namespace PacketReceivedEvents
{
    class Steering: public IExecutable {
        void execute() override;
    };


    class FlightModeChange: public IExecutable {
        void execute() override;
    };


    class PIDTuning : public IExecutable {
        void execute() override;
    };


    // events for other data packets...
}



#endif

