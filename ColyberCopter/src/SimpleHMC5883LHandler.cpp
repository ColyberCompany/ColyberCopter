/**
 * @file SimpleHMC5883LHandler.cpp
 * @author Jan Wielgus
 * @date 2021-08-12
 */

#include "../Sensors/SimpleHMC5883LHandler.h"


SimpleHMC5883LHandler::SimpleHMC5883LHandler()
{
}


bool SimpleHMC5883LHandler::initSensor()
{
    return compass.initialize();
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
