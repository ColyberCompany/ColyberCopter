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
#include "../Interfaces/IVirtualPilot.h"
#include "../Interfaces/I3DRotation.h"
#include <PID.h>


class StabilizeFlightMode : public FlightMode
{
private:
    Interfaces::I3DRotation& rotationData;
    PID levelingXPID;
    PID levelingYPID;
    PID headingHoldPID;

    float headingToHold;
    float headingError;


public:
    StabilizeFlightMode(Interfaces::I3DRotation& rotationData);

    StabilizeFlightMode(const StabilizeFlightMode&) = delete;
    StabilizeFlightMode& operator=(const StabilizeFlightMode&) = delete;

    void setLevelingXPIDGains(float kP, float kI, float kD, uint16_t Imax);
    void setLevelingYPIDGains(float kP, float kI, float kD, uint16_t Imax);
    void setHeadingHoldPIDGains(float kP, float kI, float kD, uint16_t Imax);

    void leave() override;
    void prepare() override;
    
protected:
    void flightModeLoop(ControlSticks& inputOutputSticks) override;


private:
    void updateLeveling(ControlSticks& inputOutputSticks);
    void updateHeadingHolding(ControlSticks& inputOutputSticks);
    void integrateHeadingToHold(int16_t yawStick);
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
