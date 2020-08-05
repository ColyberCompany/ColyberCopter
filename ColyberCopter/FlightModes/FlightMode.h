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
#include "Common/ControlSticks.h"


class FlightMode
{
private:
    const Enums::FlightModeTypes type;
    FlightMode* const baseFlightMode;

protected:
    static ControlSticks virtualSticks; // shared by all flight modes instance of virtual sticks


public:
    /**
     * @brief Construct a new Flight Mode object.
     * 
     * @param flightModeType Enum type of created flight mode (if new, update enum file)
     * @param baseFlightMode Pointer to flight mode that class extends
     * (nullptr if don't extend any current flight mode)
     * @param virtualPilot Pointer to VirtualPilot instance
     */
    FlightMode(Enums::FlightModeTypes flightModeType, FlightMode* baseFlightMode);

    // Disable copying instances of this class
    FlightMode(const FlightMode&) = delete;
    FlightMode& operator=(const FlightMode&) = delete;

    /**
     * @brief Does nothing.
     * Can be overriden by concrete flight modes classes.
     */
    virtual bool initializeFlightMode() = 0;

    /**
     * @brief Check if passed flight is used by this flight mode indirectly (through base flight mode)
     * or is it current one.
     * 
     * @param flightModeToCheck pointer to flight mode instance
     * to check if is used by this flight mode
     * @return true if passed flight mode is this flight mode
     * or this flight mode uses passed flight mode through base flight mode
     */
    bool checkIfRelated(const FlightMode* flightModeToCheck);

    /**
     * @return Enums::FlightModeTypes - type of this flight mode
     */
    Enums::FlightModeTypes getType();

    /**
     * @return Pointer to the only instance of control sticks shared by all flight modes.
     */
    static ControlSticks* getVirtualSticksPtr();


    /**
     * @brief Called frequently when this flight mode is selected but drone
     * is idle. Don't have to be overriden.
     * Execute runBaseFlightModeIdleLoop() method inside to execute base flight mode code.
     */
    virtual void idleLoop()
    {
        runBaseFlightModeIdleLoop();
    }

    /**
     * @brief Called with the main frequency when selected in virtual pilot.
     * Have to be overriden by concrete flight mode class.
     * INSIDE EXECUTE runBaseFlightMode() METHOD SOMEWHERE !!
     */
    virtual void run() = 0;

    /**
     * @brief Called one time when virtual pilot or any flight mode stops using this flight mode (leave from it).
     * Have to be overriden by concrete flight mode class.
     */
    virtual void leave() = 0;

    /**
     * @brief Called one time when virtual pilot didn't use but will be using now this flight mode (entering to it).
     * Have to be overriden by concrete flight mode class.
     */
    virtual void prepare() = 0;


protected:
    /**
     * @brief Used by concrete flight modes classes. Execute base flight mode code.
     * Use it at the beginning or at the end of run() method.
     */
    void runBaseFlightMode();
    
    /**
     * @brief Used by concrete flight modes to exedute idle loop
     * of their base flight modes.
     */
    void runBaseFlightModeIdleLoop();
};


#endif
