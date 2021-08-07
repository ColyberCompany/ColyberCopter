/**
 * @file QuadXMotors.cpp
 * @author Jan Wielgus
 * @date 2020-11-05
 * 
 */

#include "../Motors/QuadXMotors.h"
#include "../config.h"

using Enums::StateType;


QuadXMotors::QuadXMotors()
    : motorsTimer(TIM3)
{
}


bool QuadXMotors::initializeMotors()
{
    // https://github.com/stm32duino/wiki/wiki/HardwareTimer-library


    motorsTimer.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, FLMotorPin);
    motorsTimer.setMode(2, TIMER_OUTPUT_COMPARE_PWM1, FRMotorPin);
    motorsTimer.setMode(3, TIMER_OUTPUT_COMPARE_PWM1, BRMotorPin);
    motorsTimer.setMode(4, TIMER_OUTPUT_COMPARE_PWM1, BLMotorPin);

    motorsTimer.setPrescaleFactor(71);
    motorsTimer.setOverflow(Config::MainInterval_us, TICK_FORMAT);

    motorsTimer.setCaptureCompare(1, MinPower); // TICK_FORMAT
    motorsTimer.setCaptureCompare(2, MinPower);
    motorsTimer.setCaptureCompare(3, MinPower);
    motorsTimer.setCaptureCompare(4, MinPower);

    motorsTimer.resume();


    setState(StateType::Disabled);

    return true;
}


void QuadXMotors::updatePower(const Common::ControlSticks& stickValues)
{
    if (getState() == StateType::Enabled)
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
