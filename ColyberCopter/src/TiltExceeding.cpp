/**
 * @file TiltExceeding.cpp
 * @author Jan Wielgus
 * @date 2020-09-02
 * 
 */

#include "Failsafe/FailsafeScenarios/TiltExceeding.h"
#include "config.h"

#ifdef ARDUINO
    #include <arduino.h>
#endif

using Interfaces::I3DRotation;
using Config::TiltExceedingAngleThreshold;


TiltExceeding::TiltExceeding(I3DRotation& _rotation, IExecutable* failsafeAction)
    : FailsafeScenario(failsafeAction), rotation(_rotation)
{
}


void TiltExceeding::execute()
{
    if (checkIfAnglesExceeds())
        runFailsafeAction();
}


bool TiltExceeding::checkIfAnglesExceeds()
{
    return (abs(rotation.getPitch_deg()) > TiltExceedingAngleThreshold ||
            abs(rotation.getRoll_deg()) > TiltExceedingAngleThreshold);
}
