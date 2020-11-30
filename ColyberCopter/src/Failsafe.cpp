/**
 * @file Failsafe.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "Failsafe/Failsafe.h"
#include <LinkedList.h>


Failsafe::Failsafe()
{
    failsafeScenariosList = new LinkedList<IExecutable*>();
}


bool Failsafe::initializeFailsafe()
{
    // TODO: think if need to to anything here
}


void Failsafe::addFailsafeScenario(IExecutable* failsafeScenario)
{
    failsafeScenariosList->add(failsafeScenario);
    Serial1.println("added fail scen");
    Serial1.println((int32_t)failsafeScenario);
    delay(200);
}


void Failsafe::removeFailsafeScenario(IExecutable* failsafeScenario)
{
    // TODO: implement removeFailsafeScenario method
    // figure out how to add remove method to IList interface
    // this will cause that IArray interface will also have remove method
    // this is cool, but this also is some work to do :)
}


void Failsafe::runFailsafeCheckLoop()
{
    size_t amtOfFailsafeEvents = failsafeScenariosList->getSize();
    for (size_t i = 0; i < amtOfFailsafeEvents; i++)
        failsafeScenariosList->get(i)->execute();
}


void Failsafe::execute()
{
    runFailsafeCheckLoop();
}
