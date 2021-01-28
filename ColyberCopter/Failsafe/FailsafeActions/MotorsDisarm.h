/**
 * @file MotorsDisarm.h
 * @author Jan Wielgus
 * @brief Failsafe action that disarm immediately motors.
 * @date 2020-09-01
 * 
 */

#ifndef MOTORSDISARM_H
#define MOTORSDISARM_H

#include <IExecutable.h>
#include "../../Interfaces/IMotors.h"


class MotorsDisarm : public IExecutable
{
private:
    Interfaces::IMotors& motors;

public:
    MotorsDisarm(Interfaces::IMotors& motors);
    void execute() override;
};


#endif
