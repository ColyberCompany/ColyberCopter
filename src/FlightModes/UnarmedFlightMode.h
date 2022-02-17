/**
 * @file UnarmedFlightMode.h
 * @author Jan Wielgus
 * @brief Flight mode set when motors have to be disabled (unarmed).
 * @date 2020-12-02
 * 
 */

#ifndef UNARMEDFLIGHTMODE_H
#define UNARMEDFLIGHTMODE_H

#include "FlightMode.h"


class UnarmedFlightMode : public FlightMode
{
public:
    UnarmedFlightMode();
    UnarmedFlightMode(const UnarmedFlightMode&) = delete;
    UnarmedFlightMode& operator=(const UnarmedFlightMode&) = delete;

    void leave() override;
    void prepare() override;
    const char* getName() override;

protected:
    void flightModeLoop(Common::ControlSticks& inputOutputSticks) override;
};


#endif

