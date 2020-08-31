/**
 * @file AHRS.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "AHRS.h"


// TODO: implement constructor


void AHRS::execute()
{
    rotationCalculation->updateRotationCalculation();
    // TODO: implement other calculations
}


double AHRS::getLongitude_deg()
{
    // TODO: implement
}


double AHRS::getLatitude_deg()
{
    // TODO: implement getLongitude_deg
}


float AHRS::getAltitude_m()
{
    // TODO: implement getAltitude_m
}


float AHRS::getPitch_deg()
{
    return rotationCalculation->getAngles_deg().x;
}


float AHRS::getRoll_deg()
{
    return rotationCalculation->getAngles_deg().y;
}


float AHRS::getHeading_deg()
{
    return rotationCalculation->getAngles_deg().z;
}
