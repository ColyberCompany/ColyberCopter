/**
 * @file MotorsDisarm.h
 * @author Jan Wielgus
 * @brief Failsafe action that disarm immediately motors.
 * @date 2020-09-01
 * 
 */

#ifndef MOTORSDISARM_H
#define MOTORSDISARM_H

#include <IExecutable.h>
#include "Instances/MainInstances.h"
#include "Instances/MotorsInstance.h"

namespace FailsafeActions
{
    class DisarmMotors : public IExecutable
    {
    public:
        void execute() override {
            Instance::motors.setState(Enums::StateType::Disabled);
            Instance::virtualPilot.setFlightMode(Enums::FlightModeTypes::UNARMED);
        }
    };
}


#endif
