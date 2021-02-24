/**
 * @file TiltExceeding.cpp
 * @author Jan Wielgus
 * @date 2020-09-02
 * 
 */

#include "../Failsafe/FailsafeScenarios/TiltExceeding.h"
#include "../config.h"

#ifdef ARDUINO
    #include <Arduino.h>
#endif

using Interfaces::IAHRS;
using Config::TiltExceedingAngleThreshold;


TiltExceeding::TiltExceeding(IAHRS& _ahrs, IExecutable* failsafeAction)
    : FailsafeScenario(failsafeAction), ahrs(_ahrs)
{
}


void TiltExceeding::execute()
{
    if (checkIfAnglesExceeds())
        runFailsafeAction();
}


bool TiltExceeding::checkIfAnglesExceeds()
{
    return (abs(ahrs.getPitch_deg()) > TiltExceedingAngleThreshold ||
            abs(ahrs.getRoll_deg()) > TiltExceedingAngleThreshold);
}
