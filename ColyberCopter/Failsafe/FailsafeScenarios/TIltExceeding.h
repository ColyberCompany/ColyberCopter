/**
 * @file TiltExceeding.h
 * @author Jan Wielgus
 * @brief Failsafe scenario that thakes action if pitch or roll angle exceeds
 * the certain value.
 * @date 2020-09-02
 * 
 */

#ifndef TILTEXCEEDING_H
#define TILTEXCEEDING_H

#include "FailsafeScenario.h"
#include "Interfaces/I3DRotation.h"


class TiltExceeding : public FailsafeScenario
{
private:
    Interfaces::I3DRotation& rotation;

public:
    TiltExceeding(Interfaces::I3DRotation& rotation, IExecutable* failsafeAction);
    void execute() override;

private:
    /**
     * @brief Determines if pitch and roll are out of range.
     * 
     * @return true if angles are too high,
     * returns false if angles are nominal.
     */
    bool checkIfAnglesExceeds();
};


#endif
