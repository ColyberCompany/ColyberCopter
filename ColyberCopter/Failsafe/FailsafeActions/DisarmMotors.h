/**
 * @file MotorsDisarm.h
 * @author Jan Wielgus
 * @brief Failsafe action that disarm immediately motors.
 * @date 2020-09-01
 * 
 */

// TODO: consider making one pair of h and cpp files for all failsafe actions

#ifndef MOTORSDISARM_H
#define MOTORSDISARM_H

#include <IExecutable.h>


class DisarmMotors : public IExecutable
{
public:
    void execute() override;
};


#endif
