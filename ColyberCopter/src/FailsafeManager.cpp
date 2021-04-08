/**
 * @file FailsafeManager.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 *
 */

#include "../Failsafe/FailsafeManager.h"


bool FailsafeManager::initializeFailsafe()
{
    return true;
}


bool FailsafeManager::addFailsafeScenario(FailsafeScenario* failsafeScenario)
{
    if (failsafeScenario == nullptr)
        return false;

    if (failsafeScenariosList.contain(failsafeScenario))
        return false;

    return failsafeScenariosList.add(failsafeScenario);
}


void FailsafeManager::removeFailsafeScenario(FailsafeScenario* failsafeScenario)
{
    for (int i=0; i<failsafeScenariosList.getSize(); i++)
        if (failsafeScenariosList[i] == failsafeScenario)
        {
            failsafeScenariosList.remove(i);
            return;
        }
}


void FailsafeManager::runFailsafeCheckLoop()
{
    auto iter = failsafeScenariosList.getIterator();
    while (iter->hasNext())
        iter->next()->runFailsafeActionIfFailHasOccurred();
}


void FailsafeManager::execute()
{
    runFailsafeCheckLoop();
}
