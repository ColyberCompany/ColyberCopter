/**
 * @file FailsafeScenarios.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Definitions of all failsafe scenarios.
 * @date 2021-04-08
 * 
 */

#include "Failsafe/FailsafeScenarios/CommunicationLost.h"
#include "Failsafe/FailsafeScenarios/TiltExceeding.h"
// other failsafe scenarios...
#include "Instances/MainInstances.h"
#include "config.h"

#ifndef FAILSAFESCENARIOS_H
#define FAILSAFESCENARIOS_H

namespace FailsafeScenarios
{
    class CommunicationLost;
    class TiltExceeding;
};

#endif