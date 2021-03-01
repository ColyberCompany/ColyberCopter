
// TODO: repair all singletons with reference to the instance. It may don't work and pointers are better there.
// TODO: delete copy ctor and assignment operator in all singletons
// TODO: check if in all singletons instance are initialized as nullptr

// TODO: order includes in all files that "" are first and <> are below them

#include "Arduino.h"
#include "CopterSetup.h"
#include "Instances.h"


void setup()
{
    setupDrone();
}


void loop()
{
    Instance::tasker.runLoop();
}

