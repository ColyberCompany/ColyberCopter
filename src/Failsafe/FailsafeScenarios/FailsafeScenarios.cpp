/**
 * @file FailsafeScenarios.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Definitions of all failsafe scenarios.
 * @date 2021-04-08
 * 
 */

#include "Failsafe/FailsafeScenarios/FailsafeScenarios.h"

using namespace FailsafeScenarios;

bool CommunicationLost::hasFailOccurred()
{
    using Instance::pilotPacketComm;
    return pilotPacketComm.getConnectionStability() < ConnectionStabilityThreshold;
}


bool TiltExceeding::hasFailOccurred()
{
    using Config::TiltExceedingAngleThreshold;

    return (abs(Instance::ins.getPitch_deg()) > TiltExceedingAngleThreshold ||
            abs(Instance::ins.getRoll_deg()) > TiltExceedingAngleThreshold);
}


// other failsafe scenarios...
