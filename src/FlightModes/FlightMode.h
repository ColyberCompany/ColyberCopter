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


public:
    /**
     * @brief Construct a new Flight Mode object.
     * @param flightModeType Enum type of created flight mode (if new, update enum file).
     * @param baseFlightMode Pointer to flight mode that class extends.
     * (nullptr if don't extend any current flight mode).
     */
    FlightMode(Enums::FlightModeTypes flightModeType, FlightMode* baseFlightMode);

    // Disable copying instances of this class
    FlightMode(const FlightMode&) = delete;
    FlightMode& operator=(const FlightMode&) = delete;

    /**
     * @brief Check if passed flight is used by this flight mode indirectly (through base flight mode)
     * or is it current one.
     * @param flightModeToCheck pointer to flight mode instance
     * to check if is used by this flight mode
     * @return true if passed flight mode is this flight mode
     * or this flight mode uses passed flight mode through base flight mode
     */
    bool checkIfSuperiorOrEqualOf(const FlightMode* flightModeToCheck) const; // TODO: this name could be better

    /**
     * @return Type of this flight mode
     */
    Enums::FlightModeTypes getType();

    /**
     * @brief Can be overriden by concrete flight modes classes.
     * Prepare flight mode 
     */
    virtual bool initializeFlightMode();

    /**
     * @brief Execute flightModeLoop() of this flight mode and then of the base flight mode.
     * @param inputOutputSticks Reference to the instance where are control sticks values
     * and also there will be put the output values.
     */
    void executeFlightModeLoop(Common::ControlSticks& inputOutputSticks);

    /**
     * @brief Called once every time when this flight mode was used, but won't be used now
     * (directly as current flight mode or indirectly as base flight mode of current flight mode).
     * Have to be overriden by concrete flight mode class.
     */
    virtual void leave() = 0;

    /**
     * @brief Called once every time when this flight mode wasn't used, but will be used now
     * (directly as current flight mode or indirectly as base flight mode of current flight mode).
     * Have to be overriden by concrete flight mode class.
     */
    virtual void prepare() = 0;

    /**
     * @brief Return name of the flight mode
     */
    virtual const char* getName() = 0;

protected:
    /**
     * @brief Called with the main frequency when used as current flight mode
     * (or is used by current flight mode).
     * Have to be overriden by concrete flight mode class.
     * Don't use executeFlightModeLoop() method inside.
     */
    virtual void flightModeLoop(Common::ControlSticks& inputOutputSticks) = 0;


    /**
     * @brief Set all stick values to 0.
     */
    void resetSticks(Common::ControlSticks& sticks);
};


#endif
