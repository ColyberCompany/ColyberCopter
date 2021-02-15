/**
 * @file Failsafe.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "../Failsafe/Failsafe.h"


Failsafe::Failsafe()
{
}


bool Failsafe::initializeFailsafe()
{
    // TODO: think if need to to anything here

    return true;
}


void Failsafe::addFailsafeScenario(IExecutable* failsafeScenario)
{
    if (failsafeScenario == nullptr)
        return;

    failsafeScenariosList.add(failsafeScenario);
}


void Failsafe::removeFailsafeScenario(IExecutable* failsafeScenario)
{
    // TODO: implement removeFailsafeScenario method
    // Check index of the element to be removed and use LinkedList remove method
}


void Failsafe::runFailsafeCheckLoop()
{
    auto failsafeEventsIterator = failsafeScenariosList.getIterator();
    while (failsafeEventsIterator->hasNext())
        failsafeEventsIterator->next()->execute();
}


void Failsafe::execute()
{
    runFailsafeCheckLoop();
}
