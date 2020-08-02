/**
 * @file StabilizeFlightMode.h
 * @author Jan Wielgus
 * @brief Stabilize flight mode concrete class
 * @date 2020-08-02
 * 
 */

#ifndef STABILIZEFLIGHTMODE_H
#define STABILIZEFLIGHTMODE_H

#include "FlightMode.h"
#include "Interfaces/IVirtualPilot.h"
#include "Interfaces/I3DRotation.h"
#include <PID.h>


class StabilizeFlightMode : public FlightMode
{
private:
    PID& levelingXPID;
    PID& levelingYPID;
    PID& headingHoldPID;
    Interfaces::I3DRotation& rotationData;
    float deltaTime;

    float headingToHold;
    float headingError;


public:
    StabilizeFlightMode(Interfaces::IVirtualPilot* virtualPilot,
        PID* levelingX_PID, PID* levelingY_PID, PID* headingHold_PID,
        Interfaces::I3DRotation* rotationDataPtr, float deltaTime);

    void idleLoop() override;
    void run() override;
    void prepare() override;
    void leave() override;


private:
    void updateLeveling();
    void updateHeadingHolding();
    void integrateHeadingToHold();
    void resetSticks();
    void setHeadingToHoldToCurrentReading();
};


#endif
