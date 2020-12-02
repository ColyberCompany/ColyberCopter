/**
 * @file UnarmedFlightMode.h
 * @author Jan Wielgus
 * @brief Flight mode set when motors have to be disabled (unarmed).
 * @date 2020-12-02
 * 
 */

#ifndef UNARMEDFLIGHTMODE_H
#define UNARMEDFLIGHTMODE_H

#include "FlightMode.h"
#include "Interfaces/IMotors.h"


class UnarmedFlightMode : public FlightMode
{
private:
    Interfaces::IMotors& motors;

public:
    UnarmedFlightMode(Interfaces::IMotors& _motors)
        :FlightMode(Enums::FlightModeTypes::UNARMED, nullptr),
        motors(_motors)
    {
    }

    UnarmedFlightMode(const UnarmedFlightMode&) = delete;
    UnarmedFlightMode& operator=(const UnarmedFlightMode&) = delete;

    void leave() override
    {
        motors.setMotorsState(Enums::StateType::Enabled);
    }

    void prepare() override
    {
        motors.setMotorsState(Enums::StateType::Disabled);
    }

protected:
    void flightModeLoop(ControlSticks& inputOutputSticks) override
    {
    }
};


#endif

