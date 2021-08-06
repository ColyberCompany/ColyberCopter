/**
 * @file CommunicationLost.h
 * @author your name (you@domain.com)
 * @brief Failsafe scenario that take action when communication is lost.
 * Implementation in src/FailsafeScenarios.cpp.
 * @date 2020-09-01
 * 
 */

#ifndef COMMUNICATIONLOST_H
#define COMMUNICATIONLOST_H

#include "FailsafeScenario.h"

#ifdef ARDUINO
    #include <Arduino.h>
#endif


namespace FailsafeScenarios
{
    class CommunicationLost : public FailsafeScenario
    {
    private:
        const uint8_t ConnectionStabilityThreshold = 50;

    public:
        CommunicationLost(IExecutable* failsafeAction) : FailsafeScenario(failsafeAction) {}
        bool hasFailOccurred() override;
    };
}


#endif
