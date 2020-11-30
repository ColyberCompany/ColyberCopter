/**
 * @file CopterSetup.cpp
 * @author Jan Wielgus
 * @brief In this file all classes are connected together.
 * @date 2020-11-27
 * 
 */

#include "CopterSetup.h"
#include "config.h"
#include <SimpleTasker.h>
#include "Communication/RmtCtrlCommunication.h"
#include "Failsafe/Failsafe.h"
#include "Failsafe/FailsafeActions/MotorsDisarm.h"
#include "Failsafe/FailsafeScenarios/CommunicationLost.h"
#include "Failsafe/FailsafeScenarios/TiltExceeding.h"
#include "FlightModes/StabilizeFlightMode.h"
#include "PositionAndRotation/AHRS.h"
#include "PositionAndRotation/RotationCalculation/MadgwickIMU.h"
#include "PositionAndRotation/RotationCalculation/MadgwickAHRS.h"
#include "PositionAndRotation/PositionCalculation/NoPosCalcTemp.h"
#include "Sensors/SensorsMediator.h"
#include "Sensors/MPU6050Adapter.h"
#include "Sensors/HMC5883LAdapter.h"
#include "Motors/QuadXMotors.h"
#include "StreamComm.h"
#include "PacketCommunicationWithQueue.h"
#include "VirtualPilot.h"

using namespace Interfaces;


// Helper functions
void setupFailsafe();
void initializeSensors();
void setupFlightModes();
void addTasksToTasker();
void addPacketEvents();


// All instances
SimpleTasker simpleTasker(15);
SensorsMediator sensorsMediator;
MadgwickIMU madgwickIMU(sensorsMediator, Config::MainFrequency_Hz); // or MadgwickAHRS
NoPosCalcTemp tempNoPosCalc;
AHRS ahrs(tempNoPosCalc, madgwickIMU);
QuadXMotors quadXMotors;

// Communication
StreamComm rmtCtrlCommStream(&Serial2, Config::RmtCtrlMaxComBufferSize);
PacketCommunicationWithQueue remotePacketComm(&rmtCtrlCommStream, Config::RmtCtrlMaxQueuedBuffers); // Remote comm instance
RmtCtrlCommunication remoteControlComm(remotePacketComm);

// FlightModes
StabilizeFlightMode stabilizeFlightMode(ahrs, Config::MainInterval_s);
VirtualPilot virtualPilot(quadXMotors, stabilizeFlightMode, remoteControlComm.receiveData);

// Sensors
MPU6050Adapter mpu6050(sensorsMediator);
HMC5883LAdapter hmc5883l(sensorsMediator, mpu6050.getMPU6050Ptr());

// Failsafe
Failsafe failsafe;
MotorsDisarm failsafeActionMotorsDisarm(quadXMotors);
CommunicationLost failsafeScenarioCommLost(remotePacketComm, &failsafeActionMotorsDisarm);
TiltExceeding failsafeTiltExceeding(ahrs, &failsafeActionMotorsDisarm);



class DebugTask : public Task
{
    void execute() override
    {
        Serial.println(mpu6050.getMPU6050Ptr()->getRawAcceleration().x);
    }
};




void setupDrone()
{
    //list:
    // - 
    
    Serial.println(2);
    setupFailsafe();

    Serial.println(3);
    Serial2.begin(Config::RmtCtrlSerialBaudRate);

    Serial.println(4);

    initializeSensors();
    Serial.println(5);

    addTasksToTasker();
    Serial.println(6);

    addPacketEvents();
    Serial.println(7);
}



void setupFailsafe()
{
    // FIXME: It seems like first calling addFailsafeScenario method cause that it is called two times (when adding nullptr for example)

    failsafe.initializeFailsafe();
    //failsafe.addFailsafeScenario(&failsafeScenarioCommLost);
    //failsafe.addFailsafeScenario(&failsafeTiltExceeding);
    //failsafe.addFailsafeScenario(nullptr); // Test how many times this methods is called inside
}


void setupFlightModes()
{
    virtualPilot.addFlightMode(&stabilizeFlightMode); // TODO: think whether to pass flight modes by reference
}


void initializeSensors()
{
    Wire.begin();
    Wire.setClock(400000L);

    Serial.print("senInit");
    mpu6050.initialize();
    Serial.print(" mpuOk");
    hmc5883l.initialize();
    Serial.print(" hmcOk");
    Serial.println(" all done");
}


void addTasksToTasker()
{
    simpleTasker.addTask(&failsafe, 10, 0); // 10Hz
    simpleTasker.addTask(&ahrs, Config::MainFrequency_Hz, 0);
    simpleTasker.addTask(&mpu6050, Config::MainFrequency_Hz, 0);
    simpleTasker.addTask(&virtualPilot, Config::MainFrequency_Hz, 0);

    simpleTasker.addTask(&hmc5883l, 75, 0);// 75Hz

    // TODO: add comm


    simpleTasker.addTask(new DebugTask(), 50, 0);
}


void addPacketEvents()
{
    
}
