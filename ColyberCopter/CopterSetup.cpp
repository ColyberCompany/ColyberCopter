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
// Failsafe:
#include "Failsafe/FailsafeManager.h"
#include "Failsafe/FailsafeActions/DisarmMotors.h"
#include "Failsafe/FailsafeScenarios/CommunicationLost.h"
#include "Failsafe/FailsafeScenarios/TiltExceeding.h"
// Flight modes:
#include "FlightModes/StabilizeFlightMode.h"
#include "FlightModes/UnarmedFlightMode.h"
#include "VirtualPilot.h"
// Position and rotation calculation:
#include "PositionAndRotation/AHRS.h"
#include "PositionAndRotation/RotationCalculation/MadgwickAHRS.h"
#include "PositionAndRotation/PositionCalculation/NoPosCalcTemp.h"
// Motors:
#include "Motors/Motors.h"
#include "Motors/QuadXMotors.h"
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
#include "Sensors/NoSensor.h"
// Sensors:
#include "Sensors/SimpleMPU6050Handler.h"
#include "Sensors/SimpleHMC5883LHandler.h"

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
    SerialDebugMessenger serialDebugMessenger(Serial1);

    namespace Motors {
        QuadXMotors quadXMotors;
    }

    namespace PositionAndRotation {
        MadgwickAHRS madgwickAHRS;
        NoPosCalcTemp tempNoPosCalc;
        AHRS ahrs(tempNoPosCalc, madgwickAHRS);
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
        SimpleMPU6050Handler simpleMPU6050Handler;
        SimpleHMC5883LHandler simpleHMC5883LHandler;
        // other sensors..
        NoSensor noSensor;
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
    IVirtualPilot& virtualPilot = Assemble::virtualPilotInstance;
    PacketComm::PacketCommunication& pilotPacketComm = Assemble::Communication::rmtPacketComm;
    FailsafeManager& failsafeManager = Assemble::Failsafe::failsafeManager;
    DebugMessenger& debMes = Assemble::serialDebugMessenger;


// SensorInstances:
    using Assemble::Sensors::noSensor;
    Accelerometer& acc = Assemble::Sensors::simpleMPU6050Handler;
    Gyroscope& gyro = Assemble::Sensors::simpleMPU6050Handler;
    Magnetometer& magn = Assemble::Sensors::simpleHMC5883LHandler;
    //Barometer& baro = noSensor; // TODO: this should not compile

    // Sensor& baro = noSensor;
    // Sensor& gps = noSensor;
    // Sensor& btmRangefinder = noSensor;

// MotorsInstance:
    Motors& motors = Assemble::Motors::quadXMotors;
}



class : public IExecutable
{
    void execute() override {
        // Serial1.print(Instance::ahrs.getPitch_deg());
        // Serial1.print('\t');
        // Serial1.println(Instance::ahrs.getRoll_deg());

        // auto a = Instance::ahrs.getAbsoluteAcceleration();
        // Serial1.print(a.x);
        // Serial1.print('\t');
        // Serial1.print(a.y);
        // Serial1.print('\t');
        // Serial1.print(a.z - 1);
        // Serial1.print('\t');
        // auto angles = Instance::ahrs.getAngles_deg();
        // Serial1.print(angles.x);
        // Serial1.print('\t');
        // Serial1.print(angles.y);
        // Serial1.print('\t');
        // Serial1.println(angles.z);

        Serial1.println(Instance::ahrs.getAltitude_m());

        // Serial.println(Instance::tasker.getLoad());
    }
} debugTask;


class NaPaleTask : public IExecutable
{
    static float height_m;
    static float velocity_mps;
    static float acceleration_mpss;
    void execute() override {
        float a = (Instance::acc.get_norm().z - 1)* -9.81f;
        float aaa = (Instance::ahrs.getAbsoluteAcceleration().z - 1)* -9.81f;
        float v = velocity_mps + acceleration_mpss * Config::MainInterval_s;
        float h = height_m + velocity_mps * Config::MainInterval_s + acceleration_mpss * Config::MainInterval_s * Config::MainInterval_s / 2;

        height_m = h;
        velocity_mps = v;
        acceleration_mpss = a;

        Serial1.print(h);
        Serial1.print('\t');
        Serial1.print(a, 3);
        Serial1.print('\t');
        Serial1.println(aaa, 3);
    }
} naPaleTask;

float NaPaleTask::height_m = 0.f;
float NaPaleTask::velocity_mps = 0.f;
float NaPaleTask::acceleration_mpss = 0.f;



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
    initSensor(&Instance::acc);
    initSensor(&Instance::gyro);
    initSensor(&Instance::magn);
    //initSensor(&Instance::baro);
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
    // add other flight modes...

    Instance::virtualPilot.initializeFlightModes();
}


void addTasksToTasker()
{
    using Instance::tasker;

    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::Sensors::simpleMPU6050Handler);
    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::PositionAndRotation::ahrs);
    Assemble::TaskGroups::mainFrequency.addTask(&naPaleTask);
    Assemble::TaskGroups::mainFrequency.addTask(&Assemble::virtualPilotInstance);
    tasker.addTask_Hz(&Assemble::TaskGroups::mainFrequency, Config::MainFrequency_Hz);

    Assemble::TaskGroups::oneHertz.addTask(&Tasks::builtinDiodeBlink);
    tasker.addTask_Hz(&Assemble::TaskGroups::oneHertz, 1.f);

    tasker.addTask_Hz(&Assemble::Failsafe::failsafeManager, 10);
    tasker.addTask_Hz(&Assemble::Sensors::simpleHMC5883LHandler, 75);
    tasker.addTask_Hz(&Tasks::rmtCtrlReceiving, Config::RmtCtrlReceivingFrequency_Hz);
    tasker.addTask_Hz(&debugTask, 10);
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
