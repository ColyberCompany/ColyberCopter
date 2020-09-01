/**
 * @file FailsafeScenario.h
 * @author Jan Wielgus
 * @brief Base class for all failsafe scenarios concrete classes.
 * @date 2020-09-01
 * 
 */

#ifndef FAILSAFESCENARIO_H
#define FAILSAFESCENARIO_H

#include <IExecutable.h>


class FailsafeScenario : public IExecutable
{
private:
    IExecutable* failsafeAction;

public:
    /**
     * @brief Construct a new FailsafeScenario object.
     * 
     * @param failsafeAction This action will be executed if failsafe scenario occur.
     */
    FailsafeScenario(IExecutable* failsafeAction);
    virtual ~FailsafeScenario();
    virtual void execute() override = 0;

protected:
    /**
     * @brief Use this method if failsafe scenario will occur.
     */
    void runFailsafeAction();
};


#endif
