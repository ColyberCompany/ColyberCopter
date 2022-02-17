/**
 * @file SimpleHMC5883LHandler.cpp
 * @author Jan Wielgus
 * @date 2021-08-12
 */

#include "SimpleHMC5883LHandler.h"
#include "config.h"


SimpleHMC5883LHandler::SimpleHMC5883LHandler()
{
}


bool SimpleHMC5883LHandler::initSensor()
{
    using Config::CompassOffset;

    bool initResult = compass.initialize();
    compass.setCompassOffset(CompassOffset.x, CompassOffset.y, CompassOffset.z);

    return initResult;
}


const char* SimpleHMC5883LHandler::getName()
{
    return "hmc5883l compass";
}


Common::vector3Float SimpleHMC5883LHandler::get_norm()
{
    auto norm = compass.getNormalized();
    return Common::vector3Float(norm.x, norm.y, norm.z);
}


void SimpleHMC5883LHandler::execute()
{
    compass.readRaw();   
}
