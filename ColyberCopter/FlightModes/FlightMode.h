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

// TODO: make sure that virtual pilot put received stick data before calling current flight mode


class FlightMode
{
private:
    const Enums::FlightModeTypes type;
    FlightMode* const baseFlightMode;

protected:
    static ControlSticks virtualSticks; // shared by all flight modes instance of virtual sticks
    const float DeltaTime; // in seconds


public:
    /**
     * @brief Construct a new Flight Mode object.
     * @param flightModeType Enum type of created flight mode (if new, update enum file).
     * @param baseFlightMode Pointer to flight mode that class extends.
     * (nullptr if don't extend any current flight mode).
     * @param deltaTime Delta time of next calls of this class (in seconds).
     */
    FlightMode(Enums::FlightModeTypes flightModeType, FlightMode* baseFlightMode, float deltaTimeSec);

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
     * @brief Called frequently when this flight mode is selected as current flight mode,
     * but drone is idle. Don't have to be overriden
     * (execute base flight mode idleLoop by default).
     */
    virtual void idleLoop()
    {
        runBaseFlightModeIdleLoop();
    }

    /**
     * @brief Called with the main frequency when selected in virtual pilot.
     * Have to be overriden by concrete flight mode class.
     * CALL runBaseFlightMode() METHOD INSIDE!!
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
     * @brief Used by concrete flight modes to execute idle loop
     * of their base flight modes.
     * Use in idleLoop() method.
     */
    void runBaseFlightModeIdleLoop();

    /**
     * @brief Set all stick values to 0.
     */
    void resetSticks();
};


#endif
