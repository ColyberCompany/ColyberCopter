/**
 * @file FailsafeManager.h
 * @author Jan Wielgus
 * @brief Basic implementation of failsafe scenarios handling. Implements IFailsafe interface.
 * @date 2020-09-01
 * 
 */

#ifndef FAILSAFE_H
#define FAILSAFE_H

#include "FailsafeScenarios/FailsafeScenario.h"
#include <Task.h>
#include <LinkedList.h>

// TODO: add briefs to all methods


class FailsafeManager : public Task
{
private:
    LinkedList<FailsafeScenario*> failsafeScenariosList;

public:
    FailsafeManager();
    bool initializeFailsafe();
    void addFailsafeScenario(FailsafeScenario* failsafeScenario);
    void removeFailsafeScenario(FailsafeScenario* failsafeScenario);
    void runFailsafeCheckLoop();

protected:
    void execute() override;
};


#endif
