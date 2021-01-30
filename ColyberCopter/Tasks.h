/**
 * @file Tasks.h
 * @author Jan Wielgus
 * @brief List of all tasks and executables.
 * @date 2021-01-05
 * 
 */

#ifndef TASKS_H
#define TASKS_H

#include <Task.h>
#include "Instances.h"


namespace Tasks
{
    class : public Task
    {
        void execute() override
        {
            Instance::pilotPacketComm.receiveAndUpdatePackets();
        }
    } rmtCtrlReceiving;



    // add other tasks here
}


#endif
