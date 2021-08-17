/**
 * @file AHRS.cpp
 * @author Aleksy Walczak (aleksyww@gmail.com)
 * @date 2021-08-17
 */

#include "../PositionAndRotation/AHRS.h"
#include "../Instances/SensorInstances.h"


AHRS::AHRS(Interfaces::IPositionCalculation& _positionCalculation, Interfaces::IRotationCalculation& _rotationCalculation) 
    : positionCalculation(_positionCalculation), rotationCalculation(_rotationCalculation)
{
}

void AHRS::execute()
{
    // update rotation calculation first, because position calculation could use rotation
    rotationCalculation.updateRotationCalculation();
    positionCalculation.updatePositionCalculation();
}


Common::vector3Float AHRS::getAbsoluteAcceleration()
{
    auto acc = Instance::acc.get_norm();
    return rotationCalculation.getQuaternion().rotate3DVector(acc);
}
