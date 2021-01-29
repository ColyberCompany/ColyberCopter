/**
 * @file CommunicationLost.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "../Failsafe/FailsafeScenarios/CommunicationLost.h"


CommunicationLost::CommunicationLost(IConnectionStatus& _connectionStatus, IExecutable* failsafeAction)
    : FailsafeScenario(failsafeAction), connectionStatus(_connectionStatus)
{
}


void CommunicationLost::execute()
{
    if (connectionStatus.getConnectionStability() > ConnectionStabilityThreshold)
        runFailsafeAction();
}
