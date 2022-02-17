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


class FailsafeScenario
{
private:
    IExecutable* failsafeAction;

public:
    /**
     * @brief Construct a new FailsafeScenario object.
     * @param failsafeAction This action will be executed if failsafe scenario occur.
     */
    FailsafeScenario(IExecutable* failsafeAction);
    virtual ~FailsafeScenario();

    /**
     * @brief This method indicate whether fail action has occurred.
     * Has to be overriden by all failsafe scenarios.
     * @return true if fail has occurred and FailsafeManager need to execute failsafe action,
     * returns false otherwise.
     */
    virtual bool hasFailOccurred() = 0;

    /**
     * @brief Change failsafe action for this failsafe scenario.
     * @param failsafeAction Pointer to the failsafe action instance.
     */
    void setFailsafeAction(IExecutable* failsafeAction);

    /**
     * @brief Execute failsafe action if hasFailOccurred() method returned true.
     */
    void runFailsafeActionIfFailHasOccurred();

private:
    /**
     * @brief Use this method if failsafe scenario has occurred.
     */
    void runFailsafeAction();
};


#endif
