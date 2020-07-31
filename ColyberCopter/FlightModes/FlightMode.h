/**
 * @file FlightMode.h
 * @author Jan Wielgus
 * @brief Base abstract class for all flight modes
 * @date 2020-07-31
 * 
 */

#ifndef FLIGHTMODE_H
#define FLIGHTMODE_H

#include "Enums/FlightModeTypes.h"
#include "Interfaces/IVirtualPilot.h"
#include "Common/ControlSticks.h"


class FlightMode
{
private:
    const Enums::FlightModeTypes type;

protected:
    FlightMode* const baseFlightMode;
    static ControlSticks virtualSticks;


public:
    FlightMode(Enums::FlightModeTypes type, FlightMode* baseFlightMode, Interfaces::IVirtualPilot* virtualPilot);

    bool initializeFlightMode();
    bool checkIfRelated(const FlightMode* flightModeToCheck);
    Enums::FlightModeTypes getType();

    static ControlSticks* getVirtualSticksPtr();


    /**
     * @brief Called with the main frequency when selected in virtual pilot
     */
    virtual void run() = 0;

    /**
     * @brief Called when virtual pilot or any flight mode stops using this flight mode (leave from it)
     */
    virtual void leave() = 0;

    /**
     * @brief Called when virtual pilot didn't use but will be using now this flight mode (entering to it)
     */
    virtual void prepare() = 0;
};


#endif
