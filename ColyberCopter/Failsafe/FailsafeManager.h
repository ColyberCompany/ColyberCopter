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


class FailsafeManager : public Task
{
private:
    LinkedList<FailsafeScenario*> failsafeScenariosList;

public:
    /**
     * @return false if something went wrong, true otherwise.
     */
    bool initializeFailsafe();

    /**
     * @brief Add new FailsafeScenario to the list that will be checked
     * in a loop if has occured.
     * @param failsafeScenario Pointer to the FailsafeScenario instance.
     * @return false if failsafe scenario was not added, true otherwise.
     */
    bool addFailsafeScenario(FailsafeScenario* failsafeScenario);

    /**
     * @brief Remove FailsafeScenario so it won't be checked any more.
     * @param failsafeScenario Pointer to the FailsafeScenario
     * to be removed from the FailsafeManager list.
     */
    void removeFailsafeScenario(FailsafeScenario* failsafeScenario);

    /**
     * @brief Checks one time all previously added failsafe scenarios
     * using addFailsafeScenario() method.
     */
    void runFailsafeCheckLoop();

protected:
    void execute() override;
};


#endif
