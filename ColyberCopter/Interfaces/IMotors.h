/**
 * @file IMotors.h
 * @author Jan Wielgus
 * @brief Interface for all classes that handle motors.
 * @date 2020-09-01
 * 
 */

#ifndef IMOTORS_H
#define IMOTORS_H

#include "Common/ControlSticks.h"
#include "Enums/StateType.h"


namespace Interfaces
{
    class IMotors
    {
    public:
        virtual ~IMotors() {}

        /**
         * @brief Initialize motors.
         * 
         * @return false if something went wrong.
         * Returns true otherwise.
         */
        virtual bool initializeMotors() = 0;

        /**
         * @brief Sets the motor power.
         * 
         * @param stickValues values of virtual sticks to be set on motors.
         */
        virtual void updatePower(const ControlSticks& stickValues) = 0;

        /**
         * @brief Used to arm and disarm the motors.
         * 
         * @param state StateType::Enabled - motors are armed,
         * StateType::Disabled - motors are disarmed.
         */
        virtual void setMotorsState(Enums::StateType state) = 0;

        /**
         * @brief Checks current state of the motors.
         * 
         * @return Current state of the motors
         * (Enabled - armed, Disabled - disarmed)
         */
        virtual Enums::StateType getMotorsState() = 0;
    };
}


#endif
