/**
 * @file FailsafeManager.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 *
 */

#include "../Failsafe/FailsafeManager.h"

using SimpleDataStructures::LinkedListIterator;


bool FailsafeManager::initializeFailsafe()
{
    return true;
}


bool FailsafeManager::addFailsafeScenario(FailsafeScenario* failsafeScenario)
{
    if (failsafeScenario == nullptr)
        return false;

    if (failsafeScenariosList.contains(failsafeScenario))
        return false;

    return failsafeScenariosList.add(failsafeScenario);
}


void FailsafeManager::removeFailsafeScenario(FailsafeScenario* failsafeScenario)
{
    for (int i=0; i<failsafeScenariosList.size(); i++)
        if (failsafeScenariosList[i] == failsafeScenario)
        {
            failsafeScenariosList.remove(i);
            return;
        }
}


void FailsafeManager::runFailsafeCheckLoop()
{
    LinkedListIterator<FailsafeScenario*> iter(failsafeScenariosList);
    while (iter.hasNext())
        iter.next()->runFailsafeActionIfFailHasOccurred();
}


void FailsafeManager::execute()
{
    runFailsafeCheckLoop();
}
