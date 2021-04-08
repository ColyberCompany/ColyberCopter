/**
 * @file FailsafeManager.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "../Failsafe/FailsafeManager.h"


FailsafeManager::FailsafeManager()
{
}


bool FailsafeManager::initializeFailsafe()
{
    // TODO: think if need to to put anything here
    return true;
}


void FailsafeManager::addFailsafeScenario(FailsafeScenario* failsafeScenario)
{
    if (failsafeScenario == nullptr)
        return;

    failsafeScenariosList.add(failsafeScenario);
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
