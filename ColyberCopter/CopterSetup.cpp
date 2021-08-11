/**
 * @file CopterSetup.cpp
 * @author Jan Wielgus
 * @brief In this file all classes are connected together.
 * @date 2020-11-27
 * 
 */

// TODO: set the order of include files
#include "CopterSetup.h"
#include "config.h"
#include <Tasker.h>
#include "Failsafe/FailsafeManager.h"
#include "Failsafe/FailsafeActions/DisarmMotors.h"
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
#include <PacketCommunication.h>
#include "VirtualPilot.h"
#include "Sensors/NoSensor.h"
#include "Debug/SerialDebugMessenger.h"
#include "Common/Constants.h"
#include "Tasks.h"
#include "Communication/CommData.h"
#include "Communication/DataPackets.h"
#include "Motors/Motors.h"
#include "Common/TasksGroup.h"

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


namespace Assemble
{
    Tasker tasker(Config::MaxTaskerTasks);
    SensorsMediator sensorsMediator;
    SerialDebugMessenger serialDebugMessenger(Serial1);

    namespace Motors {
        QuadXMotors quadXMotors;
    }

    namespace PositionAndRotation {
        MadgwickIMU madgwickIMU(sensorsMediator, Config::MainFrequency_Hz); // or MadgwickAHRS
        NoPosCalcTemp tempNoPosCalc;
        AHRS ahrs(tempNoPosCalc, madgwickIMU);
    }

    namespace Communication {
        PacketComm::StreamComm<Config::RmtCtrlMaxComBufferSize> rmtCtrlCommStream(&Serial2);
        PacketComm::PacketCommunication rmtPacketComm(&rmtCtrlCommStream); // Remote comm instance
    }


    namespace FlightModes {
        UnarmedFlightMode unarmedFlightMode;
        StabilizeFlightMode stabilizeFlightMode;
    }

    VirtualPilot virtualPilotInstance(FlightModes::unarmedFlightMode);

    namespace Sensors {
        MPU6050Adapter mpu6050(sensorsMediator);
        HMC5883LAdapter hmc5883l(sensorsMediator, mpu6050.getMPU6050Ptr());
        NoSensor noSensor(sensorsMediator);
    }

    namespace Failsafe { // TODO: try to improve names of objects inside
        FailsafeManager failsafeManager;
        FailsafeActions::DisarmMotors failsafeActionDisarmMotors;
        //FailsafeScenarios::CommunicationLost failsafeScenarioCommLost(&failsafeActionDisarmMotors);
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
    IAHRS& ahrs = Assemble::PositionAndRotation::ahrs;
    ISensorsData& sensorsData = Assemble::sensorsMediator;
    IVirtualPilot& virtualPilot = Assemble::virtualPilotInstance;
    PacketComm::PacketCommunication& pilotPacketComm = Assemble::Communication::rmtPacketComm;
    FailsafeManager& failsafeManager = Assemble::Failsafe::failsafeManager;
    DebugMessenger& debMes = Assemble::serialDebugMessenger;


// SensorInstances:
    using Assemble::Sensors::noSensor;
    Sensor& accel = *Assemble::Sensors::mpu6050.getAccSensor();
    Sensor& gyro = *Assemble::Sensors::mpu6050.getGyroSensor();
    Sensor& magn = Assemble::Sensors::hmc5883l;
    Sensor& baro = noSensor;
    Sensor& gps = noSensor;
    Sensor& btmRangefinder = noSensor;

// MotorsInstance:
    Motors& motors = Assemble::Motors::quadXMotors;
}



class : public IExecutable
{
    void execute() override {
        /*
        Serial1.print(Instance::ahrs.getPitch_deg());
        Serial1.print('\t');
        Serial1.println(Instance::ahrs.getRoll_deg());*/
    }
} debugTask;




void setupDrone()
{
    using Instance::debMes;
    using Common::Consts::OKText;

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
    

    pinMode(LED_BUILTIN, OUTPUT); // TODO: this is temporary, figure something out

    debMes.showMessage("Drone setup is complete!");
}



void setupFailsafe()
{
    Instance::failsafeManager.initializeFailsafe();
    //Instance::failsafeManager.addFailsafeScenario(&Assemble::Failsafe::failsafeScenarioCommLost);
    Instance::failsafeManager.addFailsafeScenario(&Assemble::Failsafe::failsafeTiltExceeding);
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
    // add other flight modes...

    Instance::virtualPilot.initializeFlightModes();
}


void addTasksToTasker()
{
    using Instance::tasker;

    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::Sensors::mpu6050);
    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::PositionAndRotation::ahrs);
    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::virtualPilotInstance);
    tasker.addTask_Hz(&Assemble::TaskGroups::mainFrequency, Config::MainFrequency_Hz);

    Assemble::TaskGroups::oneHertz.addTask(&Tasks::builtinDiodeBlink);
    tasker.addTask_Hz(&Assemble::TaskGroups::oneHertz, 1.f);

    tasker.addTask_Hz(&Assemble::Failsafe::failsafeManager, 10);
    tasker.addTask_Hz(&Assemble::Sensors::hmc5883l, 75);
    tasker.addTask_Hz(&Tasks::rmtCtrlReceiving, Config::RmtCtrlReceivingFrequency_Hz);
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

    if (sensorInitResult == false)
    {
        Instance::debMes.showMessage("failed");
        Instance::debMes.showError(478792);
    }
    else
        Instance::debMes.showMessage("success");

    return sensorInitResult;
}
