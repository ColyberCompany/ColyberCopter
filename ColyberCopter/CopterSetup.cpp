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
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"

using namespace Interfaces;


// Helper functions
void addTasksToTasker();
void setupFailsafe();
void initializeSensors();
void setupFlightModes();
void setupCommunication();

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

    namespace Communication {
        StreamComm rmtCtrlCommStream(&Serial2, Config::RmtCtrlMaxComBufferSize);
        PacketCommunicationWithQueue rmtPacketComm(&rmtCtrlCommStream, Config::RmtCtrlMaxQueuedBuffers); // Remote comm instance
    }


    namespace FlightModes {
        UnarmedFlightMode unarmedFlightMode(quadXMotors);
    StabilizeFlightMode stabilizeFlightMode(ahrs);
    }

    VirtualPilot virtualPilotInstance(quadXMotors, FlightModes::unarmedFlightMode);

    namespace Sensors {
        MPU6050Adapter mpu6050(sensorsMediator);
        HMC5883LAdapter hmc5883l(sensorsMediator, mpu6050.getMPU6050Ptr());
        NoSensor noSensor(sensorsMediator);
    }


    Failsafe failsafe;
    MotorsDisarm failsafeActionMotorsDisarm(quadXMotors);
    CommunicationLost failsafeScenarioCommLost(Communication::rmtPacketComm, &failsafeActionMotorsDisarm);
    TiltExceeding failsafeTiltExceeding(ahrs, &failsafeActionMotorsDisarm);
}


namespace Instance
{
    ITasker& tasker = Assemble::simpleTasker;
    IAHRS& ahrs = Assemble::ahrs;
    IMotors& motors = Assemble::quadXMotors;
    ISensorsData& sensorsData = Assemble::sensorsMediator;
    IVirtualPilot& virtualPilot = Assemble::virtualPilotInstance;

    PacketCommunication& pilotPacketComm = Assemble::Communication::rmtPacketComm;

    using Assemble::Sensors::noSensor;
    Sensor& accel = *Assemble::Sensors::mpu6050.getAccSensor();
    Sensor& gyro = *Assemble::Sensors::mpu6050.getGyroSensor();
    Sensor& magn = Assemble::Sensors::hmc5883l;
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
        //Serial1.println(Instance::rotation.getPitch_deg());
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
    setupCommunication();
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
    Instance::virtualPilot.addFlightMode(&Assemble::FlightModes::unarmedFlightMode);
    Instance::virtualPilot.addFlightMode(&Assemble::FlightModes::stabilizeFlightMode); // TODO: think whether to pass flight modes by reference

    // TODO: make config values for default pid gains
    Assemble::FlightModes::stabilizeFlightMode.setLevelingXPIDGains(1.69, 0.7, 0.5, 104);
    Assemble::FlightModes::stabilizeFlightMode.setLevelingYPIDGains(1.69, 0.7, 0.5, 104);
    Assemble::FlightModes::stabilizeFlightMode.setHeadingHoldPIDGains(2.24, 1.11, 0.97, 85);

    Instance::virtualPilot.initializeFlightModes();
}


void addTasksToTasker()
{
    using Instance::tasker;

    Instance::debMes.showMessage(1);

    tasker.addTask(&Assemble::failsafe, 10);
    tasker.addTask(&Assemble::ahrs, Config::MainFrequency_Hz);
    tasker.addTask(&Assemble::Sensors::mpu6050, Config::MainFrequency_Hz);

    Instance::debMes.showMessage(2);

    tasker.addTask(&Assemble::virtualPilotInstance, Config::MainFrequency_Hz);
    tasker.addTask(&Assemble::Sensors::hmc5883l, 75);

    Instance::debMes.showMessage(3);

    tasker.addTask(&Tasks::rmtCtrlReceiving, Config::RmtCtrlReceivingFrequency_Hz);
    tasker.addTask(&debugTask, 50);
}


void setupCommunication()
{
    Serial2.begin(Config::RmtCtrlSerialBaudRate);
    Assemble::Communication::rmtCtrlCommStream.begin();
    Instance::pilotPacketComm.adaptConnStabilityToFrequency(Config::RmtCtrlReceivingFrequency_Hz);

    Instance::pilotPacketComm.addReceiveDataPacketPointer(&DataPackets::steering);
    Instance::pilotPacketComm.addReceiveDataPacketPointer(&DataPackets::flightModeChange);
    Instance::pilotPacketComm.addReceiveDataPacketPointer(&DataPackets::pidTuning);
    // add other data packets that could be received...
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
