/**
 * @file Motors.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Base class for all classes that handle motors.
 * @date 2021-03-30
 * 
 */

#ifndef MOTORS_H
#define MOTORS_H

#include "../Common/ControlSticks.h"
#include "../Enums/StateType.h"


class Motors
{
    Enums::StateType motorsState = Enums::StateType::Disabled;

public:
    virtual ~Motors() {}

    /**
     * @brief Initialize motors.
     * @return false if something went wrong.
     * Returns true otherwise.
     */
    virtual bool initializeMotors() = 0;

    /**
     * @brief Sets the motor power.
     * @param stickValues values of virtual sticks to be set on motors.
     */
    virtual void setPower(const Common::ControlSticks& stickValues) = 0;

    /**
     * @brief Used to arm and disarm the motors.
     * @param state StateType::Enabled - motors are armed,
     * StateType::Disabled - motors are disarmed.
     */
    void setState(Enums::StateType state)
    {
        motorsState = state;

        if (motorsState == Enums::StateType::Disabled)
            setPower(Common::ControlSticks(0, 0, 0, 0));
        // TODO: log motors state change
    }

    /**
     * @brief Checks current state of the motors.
     * @return Current state of the motors
     * (Enabled - armed, Disabled - disarmed)
     */
    Enums::StateType getState()
    {
        return motorsState;
    }
};


#endif
