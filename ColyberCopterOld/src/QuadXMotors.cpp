/**
 * @file QuadXMotors.cpp
 * @author Jan Wielgus
 * @date 2020-11-05
 */

// https://github.com/stm32duino/wiki/wiki/HardwareTimer-library

#include "../Motors/QuadXMotors.h"
#include "../config.h"

using Enums::StateType;
using Common::ControlSticks;


QuadXMotors::QuadXMotors()
    : timer(TIM3)
{
}


bool QuadXMotors::initializeMotors()
{
    if (Config::MainInterval_us < 2500)
        return false;

    timer.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, FLMotorPin);
    timer.setMode(2, TIMER_OUTPUT_COMPARE_PWM1, FRMotorPin);
    timer.setMode(3, TIMER_OUTPUT_COMPARE_PWM1, BRMotorPin);
    timer.setMode(4, TIMER_OUTPUT_COMPARE_PWM1, BLMotorPin);

    timer.setPrescaleFactor(72);
    timer.setOverflow(Config::MainInterval_us, TICK_FORMAT);

    timer.resume();

    setState(StateType::Disabled);

    return true;
}


void QuadXMotors::setPower(const ControlSticks& stickValues)
{
    if (getState() == StateType::Enabled)
    {
        flPower = stickValues.getThrottle() - stickValues.getPitch() + stickValues.getRoll() + stickValues.getYaw();
        frPower = stickValues.getThrottle() - stickValues.getPitch() - stickValues.getRoll() - stickValues.getYaw();
        brPower = stickValues.getThrottle() + stickValues.getPitch() - stickValues.getRoll() + stickValues.getYaw();
        blPower = stickValues.getThrottle() + stickValues.getPitch() + stickValues.getRoll() - stickValues.getYaw();

        flPower = constrain(flPower, 0, 1000);
        frPower = constrain(frPower, 0, 1000);
        brPower = constrain(brPower, 0, 1000);
        blPower = constrain(blPower, 0, 1000);
    }
    else // motors are disabled
    {
        flPower = 0;
        frPower = 0;
        brPower = 0;
        blPower = 0;
    }
}


void QuadXMotors::execute()
{
    const int16_t ZeroPulse = 1000;
    timer.setCaptureCompare(1, ZeroPulse + flPower, TICK_COMPARE_FORMAT);
    timer.setCaptureCompare(2, ZeroPulse + frPower, TICK_COMPARE_FORMAT);
    timer.setCaptureCompare(3, ZeroPulse + brPower, TICK_COMPARE_FORMAT);
    timer.setCaptureCompare(4, ZeroPulse + blPower, TICK_COMPARE_FORMAT);
}
