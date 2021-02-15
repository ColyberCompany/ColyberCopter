/**
 * @file Failsafe.h
 * @author Jan Wielgus
 * @brief Basic implementation of failsafe scenarios handling. Implements IFailsafe interface.
 * @date 2020-09-01
 * 
 */

#ifndef FAILSAFE_H
#define FAILSAFE_H

#include <Task.h>
#include <LinkedList.h>


class Failsafe : public Task
{
private:
    LinkedList<IExecutable*> failsafeScenariosList;

public:
    Failsafe();
    bool initializeFailsafe();
    void addFailsafeScenario(IExecutable* failsafeScenario);
    void removeFailsafeScenario(IExecutable* failsafeScenario);
    void runFailsafeCheckLoop();
    void execute() override;
};


#endif
