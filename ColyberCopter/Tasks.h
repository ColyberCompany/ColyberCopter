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
#include "Instances/MainInstances.h" // Exemption: this file can include Instances, because only CopterSetup.h includes this file.
#include "Instances/SensorInstances.h"


namespace Tasks
{
    class : public Task
    {
        void execute() override
        {
            Instance::pilotPacketComm.receiveAndUpdatePackets();
        }
    } rmtCtrlReceiving;



    class CalibTask : public Task
    {
        Sensor& sensor;
        bool isCalibrating_flag = false;

    public:
        CalibTask(Sensor& _sensor) : sensor(_sensor) {}

        void execute() override {
            if (!isCalibrating_flag)
            {
                uint16_t time = sensor.startBackgroundCalibration(5000);
                Instance::debMes.showMessage(time);
                pauseExecutionFor_s(time);
                isCalibrating_flag = true;
            }
            else
            {
                FloatAxisVector calib = sensor.getOffset();
                Serial1.print(calib.getAxis(Enums::AxisType::AxisX));
                Serial1.print(", ");
                Serial1.print(calib.getAxis(Enums::AxisType::AxisY));
                Serial1.print(", ");
                Serial1.println(calib.getAxis(Enums::AxisType::AxisZ));
                isCalibrating_flag = false;
            }
        }
    } calibTask(Instance::gyro);


    // add other tasks here
}


#endif
