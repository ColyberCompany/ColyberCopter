
// TODO: when class want to use instance of other class, prefer passing by reference. Check if it is like that.
// TODO: repair all singletons with reference to the instance. It may don't work and pointers are better there.
// TODO: delete copy ctor and assignment operator in all singletons
// TODO: check if in all singletons instance are initialized as nullptr

#include <SimpleTasker.h>
#include "CopterSetup.h"


SimpleTasker* taskerPtr;

// https://github.com/stm32duino/wiki/wiki/API#hardwareserial
//HardwareSerial Serial1(PA10, PA9); // Serial1 is compiling, but I don't know on which pins
HardwareSerial Serial2(PA3, PA2);
//HardwareSerial Serial3(PB11, PB10);


void setup()
{
    setupDrone();
}


void loop()
{
    simpleTasker.runLoop();
}

