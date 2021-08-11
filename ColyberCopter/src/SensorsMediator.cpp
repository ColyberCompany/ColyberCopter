/**
 * @file SensorsMediator.cpp
 * @author Jan Wielgus
 * @date 2021-08-11
 */

#include "../Sensors/SensorsMediator.h"
#include "../Instances/MainInstances.h"


SensorsMediator::SensorsMediator() 
{
    
}


Common::vector3Float* SensorsMediator::getAccReadingHandler() 
{
    if (checkInitFlag(0))
        return &accReading;
    else
        return nullptr;
}

Common::vector3Float* SensorsMediator::getGyroReadingHandler() 
{
    if (checkInitFlag(1))
        return &gyroReading;
    else
        return nullptr;
}

Common::vector3Float* SensorsMediator::getMagReadingHandler() 
{
    if (checkInitFlag(2))
        return &magReading;
    else
        return nullptr;
}

float* SensorsMediator::getPressureReadingHandler() 
{
    if (checkInitFlag(3))
        return &pressureReading;
    else
        return nullptr;
}

double* SensorsMediator::getLatitudeReadingHandler() 
{
    if (checkInitFlag(4))
        return &latitude;
    else
        return nullptr;
}

double* SensorsMediator::getLongitudeReadingHandler() 
{
    if (checkInitFlag(5))
        return &longitude;
    else
        return nullptr;
}

float* SensorsMediator::getBottomRangefinderReadingHandler() 
{
    if (checkInitFlag(6))
        return &bottomRangefinderReading;
    else
        return nullptr;
}

float* SensorsMediator::getRemperatureReadingHandler() 
{
    if (checkInitFlag(7))
        return &temperatureReading;
    else
        return nullptr;
}

bool SensorsMediator::checkInitFlag(uint8_t idx) 
{
    if (initFlags[idx] == false)
    {
        initFlags[idx] = true;
        return true;
    }
    else
    {
        Instance::debMes.showError(88728);
        return false;
    }
}
