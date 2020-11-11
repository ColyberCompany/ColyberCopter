/**
 * @file VirtualPilot.h
 * @author Jan Wielgus
 * @brief VirtualPilot is the class that handles changing flight modes and
 * transmits control values to the motors.
 * @date 2020-11-09
 * 
 */

#ifndef VIRTUALPILOT_H
#define VIRTUALPILOT_H

#include "Interfaces/IVirtualPilot.h"
#include "Interfaces/IMotors.h"
#include <Task.h>
#include "FlightModes/FlightMode.h"
#include "Communication/ReceiveData.h"


// TODO: implement VirtualPilot class
class VirtualPilot : public Interfaces::IVirtualPilot, public Task
{
private:
Interfaces::IMotors* motors;
FlightMode* currentFlightMode;
const DataFromRmtCtrl* steeringData;

public:
    VirtualPilot(Interfaces::IMotors* motors, FlightMode* initialFlightMode, const DataFromRmtCtrl* steeringData);

    void runVirtualPilot() override;
    bool setFlightMode(FlightMode* flightModeToSet) override;
    Enums::FlightModeTypes getCurrentFlightModeType() override;


private:
    /**
     * @brief Assign flight mode control sticks with data received
     * from the remote controller.
     */
    void updateFlightModesSticksWithRmtCtrlValues();

    /**
     * @brief Execute current flight mode armed or disarmed loop
     * (depending on motors state).
     */
    void executeCurrentFlightMode();

    /**
     * @brief Updates motors power using flight modes control sticks values
     * (use after execution of flight modes).
     */
    void updateMotorsPower();
};


#endif

