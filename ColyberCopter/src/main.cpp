#include <Arduino.h>
#include "CopterSetup.h"
#include "Instances/MainInstances.h"


void setup()
{
	setupDrone();
}

void loop()
{
	Instance::tasker.loop();
	
}


