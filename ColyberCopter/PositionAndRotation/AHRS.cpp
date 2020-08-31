/**
 * @file AHRS.cpp
 * @author Jan Wielgus
 * @date 2020-09-01
 * 
 */

#include "AHRS.h"

using Interfaces::IPositionCalculation;
using Interfaces::IRotationCalculation;


AHRS::AHRS(IPositionCalculation* positionCalculation, IRotationCalculation* rotationCalculation)
{
    this->positionCalculation = positionCalculation;
    this->rotationCalculation = rotationCalculation;
}


void AHRS::execute()
{
    // update rotation calculation first, because position calculation could use rotation
    rotationCalculation->updateRotationCalculation();
    positionCalculation->updatePositionCalculation();
}


double AHRS::getLongitude_deg()
{
    return positionCalculation->getLongitude_deg();
}


double AHRS::getLatitude_deg()
{
    return positionCalculation->getLatitude_deg();
}


float AHRS::getAltitude_m()
{
    return positionCalculation->getAltitude_m();
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
