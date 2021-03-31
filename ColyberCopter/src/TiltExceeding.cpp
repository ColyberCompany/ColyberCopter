/**
 * @file TiltExceeding.cpp
 * @author Jan Wielgus
 * @date 2020-09-02
 * 
 */

#include "../Failsafe/FailsafeScenarios/TiltExceeding.h"
#include "../Instances/MainInstances.h"
#include "../config.h"

#ifdef ARDUINO
    #include <Arduino.h>
#endif


TiltExceeding::TiltExceeding(IExecutable* failsafeAction)
    : FailsafeScenario(failsafeAction)
{
}


bool TiltExceeding::hasFailOccurred()
{
    using Config::TiltExceedingAngleThreshold;

    return (abs(Instance::ahrs.getPitch_deg()) > TiltExceedingAngleThreshold ||
            abs(Instance::ahrs.getRoll_deg()) > TiltExceedingAngleThreshold);
}
