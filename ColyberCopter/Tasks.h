/**
 * @file Tasks.h
 * @author Jan Wielgus
 * @brief List of all tasks and executables.
 * @date 2021-01-05
 * 
 */

#ifndef TASKS_H
#define TASKS_H

#include <IExecutable.h>
#include "Instances/MainInstances.h" // Exemption: this header file can include Instances, because only CopterSetup.h includes this file.


namespace Tasks
{
    class : public IExecutable
    {
        bool lastLedState = false;
        void execute() override {
            lastLedState = !lastLedState;
            digitalWrite(LED_BUILTIN, lastLedState);
        }
    } oneHertz;



    class : public IExecutable
    {
        void execute() override {
            Instance::pilotPacketComm.receive();
        }
    } rmtCtrlReceiving;



    // TODO: rebuild sensors calibration procedure that it automatically starts a background task and shows results at the end (and is calibrating without influencing execute() method)
    class CalibTask : private IExecutable
    {
        Sensor& sensor;
        uint16_t samples;

    public:
        CalibTask(Sensor& _sensor, uint16_t samples = 1500)
            : sensor(_sensor)
        {
            this->samples = samples;
        }

        void start(uint16_t startDelay_s = 0)
        {
            Instance::tasker.addTask_Hz(this, 1);
            if (startDelay_s > 0)
                Instance::tasker.pauseTask_s(this, startDelay_s);

            Instance::debMes.showMessage("Calibrating: ");
            Instance::debMes.showMessage(sensor.getName());

            uint16_t calibrationTime_s = sensor.startBackgroundCalibration(samples);
            Instance::debMes.showMessage(calibrationTime_s);

            Instance::tasker.pauseTask_s(this, calibrationTime_s);
        }

        void execute() override {

            Instance::debMes.showMessage("Calib end");
            auto calib = sensor.getOffset();
            Serial1.print(calib.getAxis(Enums::AxisType::AxisX));
            Serial1.print(", ");
            Serial1.print(calib.getAxis(Enums::AxisType::AxisY));
            Serial1.print(", ");
            Serial1.println(calib.getAxis(Enums::AxisType::AxisZ));

            Instance::tasker.removeTask(this);
        }
    };


    // add other tasks here
}


#endif
