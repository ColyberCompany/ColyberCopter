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


class SteeringReceivedEvent: public IExecutable
{ void execute() override; };


class FlightModeChangeReceivedEvent: public IExecutable
{ void execute() override; };


// ... (definition of other received events)


#endif

