/**
 * @file FailsafeScenario.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "../Failsafe/FailsafeScenarios/FailsafeScenario.h"


FailsafeScenario::FailsafeScenario(IExecutable* failsafeAction)
{
    this->failsafeAction = failsafeAction;
}


FailsafeScenario::~FailsafeScenario()
{
}


void FailsafeScenario::runFailsafeAction()
{
    failsafeAction->execute();
}
