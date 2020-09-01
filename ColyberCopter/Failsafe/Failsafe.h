/**
 * @file Failsafe.h
 * @author Jan Wielgus
 * @brief Basic implementation of failsafe scenarios handling. Implements IFailsafe interface.
 * @date 2020-09-01
 * 
 */

#ifndef FAILSAFE_H
#define FAILSAFE_H

#include "Interfaces/IFailsafe.h"
#include <Task.h>
#include <IList.h>


class Failsafe : public Interfaces::IFailsafe, public Task
{
private:
    IList<IExecutable*>* failsafeScenariosList;

public:
    Failsafe();
    bool initializeFailsafe() override;
    void addFailsafeScenario(IExecutable* failsafeScenario) override;
    void removeFailsafeScenario(IExecutable* failsafeScenario) override;
    void runFailsafeCheckLoop() override;
    void execute() override;
};


#endif
