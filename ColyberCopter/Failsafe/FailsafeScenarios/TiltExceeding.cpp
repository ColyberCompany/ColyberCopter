/**
 * @file TiltExceeding.cpp
 * @author Jan Wielgus
 * @date 2020-09-02
 * 
 */

#include "TiltExceeding.h"

using Interfaces::I3DRotation;


TiltExceeding::TiltExceeding(I3DRotation* rotation, IExecutable* failsafeAction)
    : FailsafeScenario(failsafeAction)
{
    this->rotation = rotation;
}


void TiltExceeding::execute()
{
    if (checkIfAnglesExceeds())
        runFailsafeAction();
}


bool TiltExceeding::checkIfAnglesExceeds()
{
    return (abs(rotation->getPitch_deg()) > AngleThreshold ||
            abs(rotation->getRoll_deg()) > AngleThreshold);
}
