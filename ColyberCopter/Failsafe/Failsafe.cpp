/**
 * @file Failsafe.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "Failsafe.h"
#include <LinkedList.h>


Failsafe::Failsafe()
{
    failsafeEventsList = new LinkedList<IExecutable*>();
}


bool Failsafe::initializeFailsafe()
{
    // TODO: think if need to to anything here
}


void Failsafe::addFailsafeEvent(IExecutable* failsafeEvent)
{
    failsafeEventsList->add(failsafeEvent);
}


void Failsafe::removeFailsafeEvent(IExecutable* failsafeEvent)
{
    // TODO: implement removeFailsafeEvent method
    // figure out how to add remove method to IList interface
    // this will cause that IArray interface will also have remove method
    // this is cool, but this also is some work to do :)
}


void Failsafe::runFailsafeCheckLoop()
{
    size_t amtOfFailsafeEvents = failsafeEventsList->getSize();
    for (size_t i = 0; i < amtOfFailsafeEvents; i++)
        failsafeEventsList->get(i)->execute();
}


void Failsafe::execute()
{
    runFailsafeCheckLoop();
}
