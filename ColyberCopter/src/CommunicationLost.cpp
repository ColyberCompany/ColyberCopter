/**
 * @file CommunicationLost.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "../Failsafe/FailsafeScenarios/CommunicationLost.h"
#include "../Instances/MainInstances.h"


CommunicationLost::CommunicationLost(IExecutable* failsafeAction)
    : FailsafeScenario(failsafeAction)
{
}


bool CommunicationLost::hasFailOccurred()
{
    using Instance::pilotPacketComm;
    return pilotPacketComm.getConnectionStability() < ConnectionStabilityThreshold;
}
