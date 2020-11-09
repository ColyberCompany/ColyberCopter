/**
 * @file RemoteControllerCommunication.cpp
 * @author Jan Wielgus
 * @brief In this file data packets are constructed.
 * @date 2020-11-09
 * 
 */

#include "RemoteControllerCommunication.h"


RemoteControllerCommunication::RemoteControllerCommunication()
{
// receive:

    // steering
    steering.addByteType(receiveData.throttle);
    steering.addByteType(receiveData.yaw);
    steering.addByteType(receiveData.pitch);
    steering.addByteType(receiveData.roll);


// send:

    // measurements and state
    // TODO: think about structure of this packet and if to split it
    measurementsAndState.addByteType(sendData.pitchAngle_deg);
    measurementsAndState.addByteType(sendData.rollAngle_deg);
    measurementsAndState.addByteType(sendData.heading_deg);
    measurementsAndState.addByteType(sendData.altitude_cm);
    measurementsAndState.addByteType(sendData.longitude);
    measurementsAndState.addByteType(sendData.latitude);
    measurementsAndState.addByteType(sendData.droneConnectionStability);
}

