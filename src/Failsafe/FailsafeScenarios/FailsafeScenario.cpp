/**
 * @file FailsafeScenario.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "Failsafe/FailsafeScenarios/FailsafeScenario.h"


FailsafeScenario::FailsafeScenario(IExecutable* failsafeAction)
{
    setFailsafeAction(failsafeAction);
}


FailsafeScenario::~FailsafeScenario()
{
}


void FailsafeScenario::setFailsafeAction(IExecutable* failsafeAction)
{
    this->failsafeAction = failsafeAction;
}


void FailsafeScenario::runFailsafeActionIfFailHasOccurred()
{
    if (hasFailOccurred())
        runFailsafeAction();
}


void FailsafeScenario::runFailsafeAction()
{
    failsafeAction->execute();
}
