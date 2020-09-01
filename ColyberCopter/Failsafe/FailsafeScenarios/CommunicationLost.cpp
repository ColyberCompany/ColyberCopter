/**
 * @file CommunicationLost.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "CommunicationLost.h"


CommunicationLost::CommunicationLost(IConnectionStatus* connectionStatus, IExecutable* failsafeAction)
    : FailsafeScenario(failsafeAction)
{
    this->connectionStatus = connectionStatus;
}


void CommunicationLost::execute()
{
    if (connectionStatus->getConnectionStability() > ConnectionStabilityThreshold)
        runFailsafeAction();
}
