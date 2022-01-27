/**
 * @file MotorsDisarm.h
 * @author Jan Wielgus
 * @brief Failsafe action that disarm immediately motors.
 * Implementation in src/FailsafeActions.cpp.
 * @date 2020-09-01
 * 
 */

#ifndef MOTORSDISARM_H
#define MOTORSDISARM_H

#include <IExecutable.h>


namespace FailsafeActions
{
    class DisarmMotors : public IExecutable
    {
    public:
        void execute() override;
    };
}


#endif
