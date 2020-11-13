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
    PID& levelingXPID; // TODO: maybe flight modes should be created inside stabilize flight mode and accessed through it's instance
    PID& levelingYPID;
    PID& headingHoldPID;
    Interfaces::I3DRotation& rotationData;

    float headingToHold;
    float headingError;


public:
    StabilizeFlightMode(PID& levelingX_PID, PID& levelingY_PID, PID& headingHold_PID,
        Interfaces::I3DRotation& rotationData, float deltaTime);

    void leave() override;
    void prepare() override;
protected:
    void disarmedLoop() override;
    void armedLoop() override;


private:
    void updateLeveling();
    void updateHeadingHolding();
    void integrateHeadingToHold();
    void calculateHeadingError();
    void setHeadingToHoldToCurrentReading();

    /**
     * @brief Makes value from parameter to be from range 0 - 360 deg.
     * Don't constrain value but makes modulo on float.
     * @param headingToCorrect Heading angle to correct.
     * @return Heading from range 0 - 360 deg.
     */
    static float correctHeading(float headingToCorrect);
};


#endif
