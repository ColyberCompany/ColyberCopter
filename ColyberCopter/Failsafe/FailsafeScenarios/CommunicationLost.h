/**
 * @file CommunicationLost.h
 * @author your name (you@domain.com)
 * @brief Failsafe scenario that take action when communication is lost.
 * @date 2020-09-01
 * 
 */

#ifndef COMMUNICATIONLOST_H
#define COMMUNICATIONLOST_H

#include "FailsafeScenario.h"

#ifdef ARDUINO
    #include <Arduino.h>
#endif


class CommunicationLost : public FailsafeScenario
{
private:
    const uint8_t ConnectionStabilityThreshold = 60; // TODO: probably it should be somewhere else

public:
    CommunicationLost(IExecutable* failsafeAction);
    void execute() override;
};


#endif
