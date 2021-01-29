/**
 * @file QuadXMotors.cpp
 * @author Jan Wielgus
 * @date 2020-11-05
 * 
 */

#include "../Motors/QuadXMotors.h"
#include "../config.h"

using Interfaces::IMotors;
using Enums::StateType;


QuadXMotors::QuadXMotors()
    : motorsTimer(TIM3)
{
    motorsState = StateType::Disabled;
}


bool QuadXMotors::initializeMotors()
{
    // https://github.com/stm32duino/wiki/wiki/HardwareTimer-library


    motorsTimer.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PA_6);
    motorsTimer.setMode(2, TIMER_OUTPUT_COMPARE_PWM1, PA_7);
    motorsTimer.setMode(3, TIMER_OUTPUT_COMPARE_PWM1, PB_0);
    motorsTimer.setMode(4, TIMER_OUTPUT_COMPARE_PWM1, PB_1);

    motorsTimer.setPrescaleFactor(71);
    motorsTimer.setOverflow(Config::MainInterval_us, TICK_FORMAT);

    motorsTimer.setCaptureCompare(1, MinPower); // TICK_FORMAT
    motorsTimer.setCaptureCompare(2, MinPower);
    motorsTimer.setCaptureCompare(3, MinPower);
    motorsTimer.setCaptureCompare(4, MinPower);

    motorsTimer.resume();


    setMotorsState(StateType::Disabled);

    return true;
}


void QuadXMotors::updatePower(const ControlSticks& stickValues)
{
    if (motorsState == StateType::Enabled)
    {
        int16_t flPower = stickValues.getThrottle() - stickValues.getPitch() + stickValues.getRoll() + stickValues.getYaw();
        int16_t frPower = stickValues.getThrottle() - stickValues.getPitch() - stickValues.getRoll() - stickValues.getYaw();
        int16_t brPower = stickValues.getThrottle() + stickValues.getPitch() - stickValues.getRoll() + stickValues.getYaw();
        int16_t blPower = stickValues.getThrottle() + stickValues.getPitch() + stickValues.getRoll() - stickValues.getYaw();

        flPower = constrain(flPower, 0, 1000);
        frPower = constrain(frPower, 0, 1000);
        brPower = constrain(brPower, 0, 1000);
        blPower = constrain(blPower, 0, 1000);

        motorsTimer.setCaptureCompare(1, MinPower + flPower); // TICK_FORMAT
        motorsTimer.setCaptureCompare(2, MinPower + frPower);
        motorsTimer.setCaptureCompare(3, MinPower + brPower);
        motorsTimer.setCaptureCompare(4, MinPower + blPower);
    }
    else // motors are disabled
    {
        motorsTimer.setCaptureCompare(1, MinPower); // TICK_FORMAT
        motorsTimer.setCaptureCompare(2, MinPower);
        motorsTimer.setCaptureCompare(3, MinPower);
        motorsTimer.setCaptureCompare(4, MinPower);
    }
}


void QuadXMotors::setMotorsState(StateType state)
{
    motorsState = state;

    if (motorsState == StateType::Disabled)
    {
        ControlSticks zeroSticks(0, 0, 0, 0);
        updatePower(zeroSticks);
    }
}


StateType QuadXMotors::getMotorsState()
{
    return motorsState;
}
