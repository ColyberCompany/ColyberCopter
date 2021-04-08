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
    // TODO: implement removeFailsafeScenario method
    // Check index of the element to be removed and use LinkedList remove method
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
