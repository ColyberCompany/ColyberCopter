/**
 * @file SimpleMS5611Continuous.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-02-27
 * 
 */

#include "SimpleMS5611Continuous.h"




SimpleMS5611Continuous::MS5611ReadingTask::MS5611ReadingTask(SimpleMS5611Continuous& _ms5611)
    : ms5611(_ms5611)
{
}


void SimpleMS5611Continuous::MS5611ReadingTask::execute()
{
    // TODO: replace if brackets contents with bool methods
    if (actionCounter >= 1 &&
        actionCounter < SimpleMS5611Continuous::PressurePerTemperatureRequests)
    {
        // read pressure and request next pressure

        ms5611.getRawPressureFromDevice();
        ms5611.requestPressureFromDevice();
    }
    else if (actionCounter == SimpleMS5611Continuous::PressurePerTemperatureRequests)
    {
        // read pressure and request next temperature

        ms5611.getRawPressureFromDevice();
        ms5611.requestTemperatureFromDevice();
    }
    else if (actionCounter == SimpleMS5611Continuous::PressurePerTemperatureRequests + 1) // should be only when actionCounter == PressurePerTemperatureRequests + 1
    {
        // read temperature and request next pressure, reset actionCounter

        ms5611.getRawTemperatureFromDevice();
        ms5611.requestPressureFromDevice();
        actionCounter = 0; // 0 because incrementation is at the end
    }
    else if (actionCounter == 0) // first pressure request
    {
        ms5611.requestPressureFromDevice();
    }

    ms5611.calculatePressureAndTemperatureFromRawData();

    // Pressure is the average value of PressurePerTemperatureRequests + 1 readings
    ms5611.pressureFilter.update(ms5611.intPressure);
    ms5611.pressure = ms5611.pressureFilter.getFilteredValueFloat();

    // Smooth the value
	if (abs(ms5611.smoothPressure - ms5611.pressure) > 1)
		ms5611.smoothPressure = ms5611.smoothPressure*0.72f + ms5611.pressure*0.28f;
	else
		ms5611.smoothPressure = ms5611.smoothPressure*0.96f + ms5611.pressure*0.04f;

    ms5611.executeNewReadingEvent();

    actionCounter++;
}





SimpleMS5611Continuous::SimpleMS5611Continuous(ITasker& _tasker)
    : tasker(_tasker),
    pressureFilter(PressurePerTemperatureRequests + 1),
    readingTask(*this)
{
}


bool SimpleMS5611Continuous::initialize()
{
    if (!SimpleMS5611::initialize())
        return false;

    float readingTaskFrequency = 1000000.f / RequestWaitTime_us;
    tasker.addTask(&readingTask, readingTaskFrequency);
    
    return true;
}


void SimpleMS5611Continuous::setNewReadingEvent(IExecutable* newReadingEvent)
{
    this->newReadingEvent = newReadingEvent;
}


void SimpleMS5611Continuous::executeNewReadingEvent()
    {
        if (newReadingEvent != nullptr)
            newReadingEvent->execute();
    }
