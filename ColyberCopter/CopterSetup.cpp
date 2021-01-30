/**
 * @file CopterSetup.cpp
 * @author Jan Wielgus
 * @brief In this file all classes are connected together.
 * @date 2020-11-27
 * 
 */

#include "CopterSetup.h"
#include "Instances.h"
#include "config.h"
#include <SimpleTasker.h>
#include "Communication/RemoteControlComm.h"
#include "Failsafe/Failsafe.h"
#include "Failsafe/FailsafeActions/MotorsDisarm.h"
#include "Failsafe/FailsafeScenarios/CommunicationLost.h"
#include "Failsafe/FailsafeScenarios/TiltExceeding.h"
#include "FlightModes/StabilizeFlightMode.h"
#include "FlightModes/UnarmedFlightMode.h"
#include "PositionAndRotation/AHRS.h"
#include "PositionAndRotation/RotationCalculation/MadgwickIMU.h"
#include "PositionAndRotation/RotationCalculation/MadgwickAHRS.h"
#include "PositionAndRotation/PositionCalculation/NoPosCalcTemp.h"
#include "Sensors/SensorsMediator.h"
#include "Sensors/MPU6050Adapter.h"
#include "Sensors/HMC5883LAdapter.h"
#include "Motors/QuadXMotors.h"
#include <StreamComm.h>
#include <PacketCommunicationWithQueue.h>
#include "VirtualPilot.h"
#include "Sensors/NoSensor.h"
#include "Debug/SerialDebugMessenger.h"
#include "Common/Constants.h"
#include "Tasks.h"

using namespace Interfaces;


// Helper functions
void addTasksToTasker();
void setupFailsafe();
void initializeSensors();
void setupFlightModes();
void setupRemoteControllerComm();


// https://github.com/stm32duino/wiki/wiki/API#hardwareserial
//HardwareSerial Serial1(PA10, PA9); // Serial1 is compiling, but I don't know on which pins
HardwareSerial Serial2(PA3, PA2);
//HardwareSerial Serial3(PB11, PB10);


namespace Assemble
{
    SimpleTasker simpleTasker(Config::MaxTaskerTasks);
    SensorsMediator sensorsMediator;
    MadgwickIMU madgwickIMU(sensorsMediator, Config::MainFrequency_Hz); // or MadgwickAHRS
    NoPosCalcTemp tempNoPosCalc;
    AHRS ahrs(tempNoPosCalc, madgwickIMU);
    QuadXMotors quadXMotors;
    SerialDebugMessenger serialDebugMessenger(Serial1);

    // Communication
    StreamComm rmtCtrlCommStream(&Serial2, Config::RmtCtrlMaxComBufferSize);
    PacketCommunicationWithQueue rmtPacketComm(&rmtCtrlCommStream, Config::RmtCtrlMaxQueuedBuffers); // Remote comm instance
    RemoteControlComm remoteControlComm(rmtPacketComm);

    // FlightModes
    UnarmedFlightMode unarmedFlightMode(quadXMotors);
    StabilizeFlightMode stabilizeFlightMode(ahrs);
    VirtualPilot virtualPilotInstance(quadXMotors, unarmedFlightMode, remoteControlComm.receiveStuff.data);

    // Sensors
    MPU6050Adapter mpu6050(sensorsMediator);
    HMC5883LAdapter hmc5883l(sensorsMediator, mpu6050.getMPU6050Ptr());
    NoSensor noSensor(sensorsMediator);

    // Failsafe
    Failsafe failsafe;
    MotorsDisarm failsafeActionMotorsDisarm(quadXMotors);
    CommunicationLost failsafeScenarioCommLost(rmtPacketComm, &failsafeActionMotorsDisarm);
    TiltExceeding failsafeTiltExceeding(ahrs, &failsafeActionMotorsDisarm);
}


namespace Instance
{
    ITasker& tasker = Assemble::simpleTasker;
    I3DPosition& position = Assemble::ahrs;
    I3DRotation& rotation = Assemble::ahrs;
    IMotors& motors = Assemble::quadXMotors;
    ISensorsData& sensorsData = Assemble::sensorsMediator;
    IVirtualPilot& virtualPilot = Assemble::virtualPilotInstance;

    PacketCommunication& pilotPacketComm = Assemble::rmtPacketComm;
    RemoteControlComm& pilotPacketsAndData = Assemble::remoteControlComm;

    using Assemble::noSensor;
    Sensor& accel = *Assemble::mpu6050.getAccSensor();
    Sensor& gyro = *Assemble::mpu6050.getGyroSensor();
    Sensor& magn = Assemble::hmc5883l;
    Sensor& baro = noSensor;
    Sensor& gps = noSensor;
    Sensor& btmRangefinder = noSensor;

    Failsafe& failsafe = Assemble::failsafe;
    DebugMessenger& debMes = Assemble::serialDebugMessenger;
}



class : public Task
{
    void execute() override
    {
        Serial1.println(Instance::rotation.getPitch_deg());
    }
} debugTask;




void setupDrone()
{
    using Instance::debMes;
    using Consts::OKText;

    debMes.enableAndInitialize(); // Comment this line to disable all debug messages
    debMes.showMessage("Beginning drone setup");
    delay(10);


    addTasksToTasker();


    debMes.showMessage("Failsafe");
    setupFailsafe();
    debMes.showMessage(OKText);


    debMes.showMessage("Sensors");
    initializeSensors();
    debMes.showMessage(OKText);


    debMes.showMessage("FlightModes");
    setupFlightModes();
    debMes.showMessage(OKText);


    debMes.showMessage("RmtCtrlComm");
    setupRemoteControllerComm();
    debMes.showMessage(OKText);


    debMes.showMessage("Motors");
    Instance::motors.initializeMotors();
    debMes.showMessage(OKText);
    

    debMes.showMessage("Drone setup is complete!");
}



void setupFailsafe()
{
    // BUG: here
    // FIXME: It seems like first calling addFailsafeScenario method cause that it is called two times (when adding nullptr for example)

    Instance::failsafe.initializeFailsafe();
    //failsafe.addFailsafeScenario(&failsafeScenarioCommLost);
    //failsafe.addFailsafeScenario(&failsafeTiltExceeding);
    //failsafe.addFailsafeScenario(nullptr); // Test how many times this methods is called inside
}


void initializeSensors()
{
    using Instance::debMes;

    Wire.begin();
    delay(100);

    if (!Assemble::mpu6050.initialize()) // TODO: this is because initializations below don't initialize mpu6050, try to get rid of this
        debMes.showErrorAndAbort(100);
    
    if (!Assemble::hmc5883l.initialize())
        debMes.showErrorAndAbort(101);

    // Check other key sensors ...


    // Maybe check each sensor separately? <<<<<<<<<<<<<<< ??
    bool initFlag = true;
    initFlag &= Instance::accel.initialize();
    initFlag &= Instance::gyro.initialize();
    initFlag &= Instance::magn.initialize();
    initFlag &= Instance::baro.initialize();
    initFlag &= Instance::gps.initialize();
    initFlag &= Instance::btmRangefinder.initialize();
    if (!initFlag)
        debMes.showErrorAndAbort(58462);
    

    // Set fast 400kHz I2C clock
    Wire.setClock(400000L);
}


void setupFlightModes()
{
    Instance::virtualPilot.addFlightMode(&Assemble::unarmedFlightMode);
    Instance::virtualPilot.addFlightMode(&Assemble::stabilizeFlightMode); // TODO: think whether to pass flight modes by reference

    Instance::virtualPilot.initializeFlightModes();
}


void addTasksToTasker()
{
    using Instance::tasker;

    Instance::debMes.showMessage(1);

    tasker.addTask(&Assemble::failsafe, 10);
    tasker.addTask(&Assemble::ahrs, Config::MainFrequency_Hz);
    tasker.addTask(&Assemble::mpu6050, Config::MainFrequency_Hz);

    Instance::debMes.showMessage(2);

    tasker.addTask(&Assemble::virtualPilotInstance, Config::MainFrequency_Hz);
    tasker.addTask(&Assemble::hmc5883l, 75);

    Instance::debMes.showMessage(3);

    tasker.addTask(&Tasks::rmtCtrlReceiving, Config::RmtCtrlReceivingFrequency_Hz);
    tasker.addTask(&debugTask, 50);
}


void setupRemoteControllerComm()
{
    Serial2.begin(Config::RmtCtrlSerialBaudRate);
    Assemble::rmtCtrlCommStream.begin();
    Instance::pilotPacketComm.adaptConnStabilityToFrequency(Config::RmtCtrlReceivingFrequency_Hz);
}
