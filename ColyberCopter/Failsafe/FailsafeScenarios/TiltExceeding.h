/**
 * @file TiltExceeding.h
 * @author Jan Wielgus
 * @brief Failsafe scenario that thakes action if pitch or roll angle exceeds
 * the certain value.
 * Implementation in src/FailsafeScenarios.cpp.
 * @date 2020-09-02
 * 
 */

#ifndef TILTEXCEEDING_H
#define TILTEXCEEDING_H

#include "FailsafeScenario.h"


namespace FailsafeScenarios
{
    class TiltExceeding : public FailsafeScenario
    {
    public:
        TiltExceeding(IExecutable* failsafeAction) : FailsafeScenario(failsafeAction) {}
        bool hasFailOccurred() override;
    };
}


#endif
