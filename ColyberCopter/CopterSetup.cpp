/**
 * @file CopterSetup.cpp
 * @author Jan Wielgus
 * @brief In this file all classes are connected together.
 * @date 2020-11-27
 * 
 */

// TODO: set the order of include files
#include "CopterSetup.h"
#include "Instances.h"
#include "config.h"
#include <SimpleTasker.h>
#include "Communication/RemoteControlComm.h"
#include "Failsafe/Failsafe.h"
#include "Failsafe/FailsafeActions/MotorsDisarm.h"
#include "Failsafe/FailsafeScenarios/CommunicationLost.h"
#include "Failsafe/FailsafeScenarios/TiltExceeding.h"
#include "FlightModes/UnarmedFlightMode.h"
#include "FlightModes/StabilizeFlightMode.h"
#include "FlightModes/AltHoldFlightMode.h"
#include "PositionAndRotation/AHRS.h"
#include "PositionAndRotation/RotationCalculation/MadgwickIMU.h"
#include "PositionAndRotation/RotationCalculation/MadgwickAHRS.h"
#include "PositionAndRotation/PositionCalculation/NoPosCalcTemp.h"
#include "Sensors/SensorsMediator.h"
#include "Sensors/MPU6050Adapter.h"
#include "Sensors/HMC5883LAdapter.h"
#include "Sensors/MS5611Adapter.h"
#include "Sensors/NoSensor.h"
#include "Motors/QuadXMotors.h"
#include <StreamComm.h>
#include <PacketCommunicationWithQueue.h>
#include "VirtualPilot.h"
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

// Helper^2 functions
bool initSensor(Sensor* sensorToInit);


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
    AltHoldFlightMode altHoldFlightMode(stabilizeFlightMode, ahrs);
    VirtualPilot virtualPilotInstance(quadXMotors, unarmedFlightMode, remoteControlComm.receiving.data);

    // Sensors
    MPU6050Adapter mpu6050(sensorsMediator);
    HMC5883LAdapter hmc5883l(sensorsMediator, mpu6050.getMPU6050Ptr());
    MS5611Adapter ms5611(sensorsMediator, simpleTasker);
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
    IAHRS& ahrs = Assemble::ahrs;
    IMotors& motors = Assemble::quadXMotors;
    ISensorsData& sensorsData = Assemble::sensorsMediator;
    IVirtualPilot& virtualPilot = Assemble::virtualPilotInstance;

    PacketCommunication& pilotPacketComm = Assemble::rmtPacketComm;
    RemoteControlComm& pilotPacketsAndData = Assemble::remoteControlComm;

    using Assemble::noSensor;
    Sensor& accel = *Assemble::mpu6050.getAccSensor();
    Sensor& gyro = *Assemble::mpu6050.getGyroSensor();
    Sensor& magn = Assemble::hmc5883l;
    Sensor& baro = Assemble::ms5611;
    Sensor& gps = noSensor;
    Sensor& btmRangefinder = noSensor;

    Failsafe& failsafe = Assemble::failsafe;
    DebugMessenger& debMes = Assemble::serialDebugMessenger;
}



class : public Task
{
    void execute() override
    {
        //Serial1.println(Instance::sensorsData.getPressure_mbar());
    }
} debugTask;




void setupDrone()
{
    using Instance::debMes;
    using Consts::OKText;

    debMes.enableAndInitialize(); // Comment this line to disable all debug messages
    debMes.showMessage("Beginning drone setup");
    delay(100);


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
    Instance::failsafe.initializeFailsafe();
    //Instance::failsafe.addFailsafeScenario(&Assemble::failsafeScenarioCommLost);
    Instance::failsafe.addFailsafeScenario(&Assemble::failsafeTiltExceeding);
}


void initializeSensors()
{
    Wire.begin();
    delay(100);


    // TODO: make a list from sensors and add enum with sensor types
    initSensor(&Instance::accel);
    initSensor(&Instance::gyro);
    initSensor(&Instance::magn);
    initSensor(&Instance::baro);
    initSensor(&Instance::gps);
    initSensor(&Instance::btmRangefinder);
    // new sensors goes here...
    

    // Set fast 400kHz I2C clock
    Wire.setClock(400000L);
}


void setupFlightModes()
{
    Instance::virtualPilot.addFlightMode(&Assemble::unarmedFlightMode);
    Instance::virtualPilot.addFlightMode(&Assemble::stabilizeFlightMode); // TODO: think whether to pass flight modes by reference

    // TODO: make config values for default pid gains
    Assemble::stabilizeFlightMode.setLevelingXPIDGains(1.69, 0.7, 0.5, 104);
    Assemble::stabilizeFlightMode.setLevelingYPIDGains(1.69, 0.7, 0.5, 104);
    Assemble::stabilizeFlightMode.setHeadingHoldPIDGains(2.24, 1.11, 0.97, 85);
    //Assemble::altHoldFlightMode.setAltHoldPIDGains(0.f, 0.f, 0.f, 0); // TODO: set default alt hold pid gains

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






bool initSensor(Sensor* sensorToInit)
{
    Instance::debMes.showMessage("Initializing:"); // TODO: add variadic version of showMessage that receive multiple strings to show and use it there
    Instance::debMes.showMessage(sensorToInit->getName());

    bool sensorInitResult = sensorToInit->initialize();

    if (sensorInitResult == false)
    {
        Instance::debMes.showMessage("failed");
        Instance::debMes.showError(478792);
    }
    else
        Instance::debMes.showMessage("success");

    return sensorInitResult;
}
