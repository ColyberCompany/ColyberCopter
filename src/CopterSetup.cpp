/**
 * @file CopterSetup.cpp
 * @author Jan Wielgus
 * @brief In this file all classes are connected together.
 * @date 2020-11-27
 * 
 */

// General:
#include "CopterSetup.h"
#include "config.h"
#include <Tasker.h>
#include "Tasks.h"
#include "Common/Constants.h"
#include "Common/Utils.h"
#include <SPI.h>
// Failsafe:
#include "Failsafe/FailsafeManager.h"
#include "Failsafe/FailsafeActions/DisarmMotors.h"
#include "Failsafe/FailsafeScenarios/CommunicationLost.h"
#include "Failsafe/FailsafeScenarios/TiltExceeding.h"
// Flight modes:
#include "FlightModes/UnarmedFlightMode.h"
#include "FlightModes/StabilizeFlightMode.h"
#include "FlightModes/AltHoldFlightMode.h"
#include "NavigationSystem/VirtualPilot.h"
// Navigation system:
#include "NavigationSystem/INS.h"
// Motors:
#include "Motors/Motors.h"
#include "Motors/QuadXMotors.h"
#include "Motors/NoMotors.h"
// Communication:
#include <StreamComm.h>
#include <PacketCommunication.h>
#include "Debug/SerialDebugMessenger.h"
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"
#include "Common/TasksGroup.h"
// Sensors base:
#include "Sensors/Base/Accelerometer.h"
#include "Sensors/Base/Gyroscope.h"
#include "Sensors/Base/Magnetometer.h"
#include "Sensors/Base/Barometer.h"
#include "Sensors/Base/GPS.h"
#include "Sensors/Base/Rangefinder.h"
#include "Sensors/Base/TemperatureSensor.h"
// Sensors:
#include "Sensors/SimpleMPU6050Handler.h"
#include "Sensors/MPU6500SPIHandler.h"
#include "Sensors/SimpleHMC5883LHandler.h"
#include "Sensors/SimpleMS5611Handler.h"

using namespace Interfaces;


// Setup functions
void addTasksToTasker();
void setupFailsafe();
void initializeSensors();
void setupFlightModes();
void setupCommunication();

// Helper functions
bool initSensor(Sensor* sensorToInit);


// https://github.com/stm32duino/wiki/wiki/API#hardwareserial
//HardwareSerial Serial1(PA10, PA9); // Serial1 is compiling, but I don't know on which pins
HardwareSerial Serial2(PA3, PA2);
//HardwareSerial Serial3(PB11, PB10);

SPIClass SPI_2(PB15, PB14, PB13, PB12);


namespace Assemble
{
    Tasker tasker(Config::MaxTaskerTasks);
    SerialDebugMessenger serialDebugMessenger(Serial1);

    namespace Motors {
        #ifdef COLYBER_DEACTIVATE_MOTORS
        NoMotors noMotors;
        #else
        QuadXMotors quadXMotors;
        #endif
    }

    namespace NavigationSystem {
        INS ins;
    }

    namespace Communication {
        PacketComm::StreamComm<Config::RmtCtrlMaxComBufferSize> rmtCtrlCommStream(&Serial2);
        PacketComm::PacketCommunication rmtPacketComm(&rmtCtrlCommStream); // Remote comm instance
    }

    namespace FlightModes {
        UnarmedFlightMode unarmedFlightMode;
        StabilizeFlightMode stabilizeFlightMode;
        AltHoldFlightMode altHoldFlightMode(stabilizeFlightMode);
    }

    VirtualPilot virtualPilotInstance(FlightModes::unarmedFlightMode);

    namespace Sensors {
        SimpleMPU6050Handler simpleMPU6050Handler;
        // MPU6500SPIHandler mpu6500spiHandler(SPI_2, PB12);
        #if COLYBER_MAGN == COLYBER_SENSOR_HMC5883L
        SimpleHMC5883LHandler simpleHMC5883LHandler;
        #endif
        SimpleMS5611Handler simpleMS5611Handler;
        // other sensors..
    }

    namespace Failsafe { // TODO: try to improve names of objects inside
        FailsafeManager failsafeManager;
        FailsafeActions::DisarmMotors failsafeActionDisarmMotors;
        FailsafeScenarios::CommunicationLost failsafeScenarioCommLost(&failsafeActionDisarmMotors);
        FailsafeScenarios::TiltExceeding failsafeTiltExceeding(&failsafeActionDisarmMotors);
    }

    namespace TaskGroups {
        Common::TasksGroup mainFrequency(5);
        Common::TasksGroup oneHertz(4);
    }
}


namespace Instance
{
// MainInstances:
    Tasker& tasker = Assemble::tasker;
    INS& ins = Assemble::NavigationSystem::ins;
    IVirtualPilot& virtualPilot = Assemble::virtualPilotInstance;
    PacketComm::PacketCommunication& pilotPacketComm = Assemble::Communication::rmtPacketComm;
    FailsafeManager& failsafeManager = Assemble::Failsafe::failsafeManager;
    DebugMessenger& debMes = Assemble::serialDebugMessenger;


// SensorInstances:
    Accelerometer& acc = Assemble::Sensors::simpleMPU6050Handler;
    Gyroscope& gyro = Assemble::Sensors::simpleMPU6050Handler;
    #ifdef COLYBER_USE_MAGN
    Magnetometer& magn =
        #if COLYBER_MAGN == COLYBER_SENSOR_HMC5883L
        Assemble::Sensors::simpleHMC5883LHandler;
        #endif
    #endif
    Barometer& baro = Assemble::Sensors::simpleMS5611Handler;
    TemperatureSensor& temperature = Assemble::Sensors::simpleMS5611Handler;


// MotorsInstance:
    #ifdef COLYBER_DEACTIVATE_MOTORS
    Motors& motors = Assemble::Motors::noMotors;
    #else
    Motors& motors = Assemble::Motors::quadXMotors;
    #endif
}



class : public IExecutable
{
    void execute() override {
        using Common::Utils::printVector3;

        //printVector3(Instance::ins.getAngles_deg());
    }
} debugTask;




void setupDrone()
{
    using Instance::debMes;
    using Common::Consts::OKText;

    debMes.enableAndInitialize(); // Comment this line to disable all debug messages
    debMes.showMessage("Beginning drone setup");
    delay(200);


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
    Instance::motors.initializeMotors(); // TODO: initialize in separate func and check return value
    debMes.showMessage(OKText);


    addTasksToTasker();
    

    pinMode(LED_BUILTIN, OUTPUT); // TODO: this is temporary, figure something out

    debMes.showMessage("Drone setup is complete!");
}



void setupFailsafe()
{
    Instance::failsafeManager.initializeFailsafe();
    Instance::failsafeManager.addFailsafeScenario(&Assemble::Failsafe::failsafeScenarioCommLost);
    Instance::failsafeManager.addFailsafeScenario(&Assemble::Failsafe::failsafeTiltExceeding);
}


// TODO: [#86] stop program if at least one sensor wasn't successfully initialized (all non-disabled sensors by macro)
void initializeSensors()
{
    Wire.begin();
    delay(100);
    SPI_2.begin();
    delay(50);


    // TODO: make a list from sensors and add enum with sensor types
    initSensor(&Instance::acc);
    initSensor(&Instance::gyro);
    #ifdef COLYBER_USE_MAGN
    initSensor(&Instance::magn);
    #endif
    initSensor(&Instance::baro);
    //initSensor(&Instance::gps);
    //initSensor(&Instance::btmRangefinder);
    // new sensors goes here...
    

    // Set fast 400kHz I2C clock
    Wire.setClock(400000L);
}


void setupFlightModes()
{
    Instance::virtualPilot.addFlightMode(&Assemble::FlightModes::unarmedFlightMode);
    Instance::virtualPilot.addFlightMode(&Assemble::FlightModes::stabilizeFlightMode); // TODO: think whether to pass flight modes by reference
    Instance::virtualPilot.addFlightMode(&Assemble::FlightModes::altHoldFlightMode);
    // add other flight modes...

    Instance::virtualPilot.initializeFlightModes(); // TODO: this method returns false if not all flight modes were initialized. This should be checked!
}


void addTasksToTasker()
{
    using Instance::tasker;

    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::Sensors::simpleMPU6050Handler);
    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::NavigationSystem::ins);
    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::virtualPilotInstance);
    #ifndef COLYBER_DEACTIVATE_MOTORS
    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::Motors::quadXMotors);
    #endif
    tasker.addTask_us(&Assemble::TaskGroups::mainFrequency, Config::MainInterval_us);

    Assemble::TaskGroups::oneHertz.addTask(&Tasks::builtinDiodeBlink);
    tasker.addTask_Hz(&Assemble::TaskGroups::oneHertz, 1.f);

    tasker.addTask_Hz(&Assemble::Failsafe::failsafeManager, 10);
    #if COLYBER_MAGN == COLYBER_SENSOR_HMC5883L
    tasker.addTask_Hz(&Assemble::Sensors::simpleHMC5883LHandler, 75);
    #endif
    tasker.addTask_us(&Assemble::Sensors::simpleMS5611Handler, SimpleMS5611Handler::RequestWaitTime_us, TaskType::NO_CATCHING_UP);
    tasker.addTask_Hz(&Tasks::rmtCtrlReceiving, Config::RmtCtrlReceivingFrequency_Hz);
    tasker.addTask_Hz(&Tasks::rmtCtrlSendingDroneData, 10);
    tasker.addTask_Hz(&debugTask, 50);
}


void setupCommunication()
{
    Serial2.begin(Config::RmtCtrlSerialBaudRate);
    Instance::pilotPacketComm.adaptConnStabilityToFrequency(Config::RmtCtrlReceivingFrequency_Hz);

    Instance::pilotPacketComm.registerReceivePacket(&DataPackets::steering);
    Instance::pilotPacketComm.registerReceivePacket(&DataPackets::flightModeChange);
    Instance::pilotPacketComm.registerReceivePacket(&DataPackets::pidTuning);
    // add other data packets that could be received...
}






bool initSensor(Sensor* sensorToInit)
{
    Instance::debMes.showMessage("Initializing:");
    Instance::debMes.showMessage(sensorToInit->getName());

    bool sensorInitResult = sensorToInit->initialize();
    delay(20);

    if (sensorInitResult == false)
    {
        Instance::debMes.showMessage("failed");
        Instance::debMes.showErrorAndAbort(478792);
    }
    else
        Instance::debMes.showMessage("success");

    return sensorInitResult;
}
