/**
 * @file IVirtualPilot.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */


#ifndef IVIRTUALPILOT_H
#define IVIRTUALPILOT_H

#include "FlightModes/FlightMode.h"
#include "Enums/FlightModeTypes.h"


// TODO: remove this note if issue is done
// Flight modes setting could be done in a different way.
// There is no need to store array of fligt modes and set it by the enum.
// Just don't make a fm list and set the flight mode by passing a pointer to the
// flight mode that need to be set. All fms can be created inside this class (or not, think about that
// if flight modes are created outside, it will be easier to add new flight modes later).
// 


namespace Interfaces
{
    class IVirtualPilot
    {
    public:
        virtual ~IVirtualPilot() {}

        /**
         * @brief Used to enable proper work of prepare() and leave() flight modes methods.
         * @return false when flight mode of this type was already added.
         */
        virtual bool addFlightMode(FlightMode* flightMode) = 0;

        /**
         * @brief Executes initializeFlightMode methods of all added flight modes.
         * @return false if at least one flight mode return false during initialization.
         * Returns true otherwise.
         */
        virtual bool initializeFlightModes() = 0;

        /**
         * @brief Used whenever want to change the current flight mode.
         * If flight modes are added using addFlightMode() method
         * change will be smooth (leave() and prepare() methods of
         * proper flight modes will be executed)
         * @param flightModeToSet Pointer to the flight mode instance to set.
         * @return false if instance of choosen flight mode was not found
         * (wasn't added using addFlightMode() method).
         */
        virtual bool setFlightMode(Enums::FlightModeTypes flightModeToSetType) = 0;

        /**
         * @brief Executes the virtual pilot once.
         * If virtual pilot instance extends Task clas (could be used in Tasker)
         * execute() method should execute this method inside.
         */
        virtual void runVirtualPilot() = 0;

        /**
         * @brief Get type of the current flight mode.
         */
        virtual Enums::FlightModeTypes getCurrentFlightModeType() = 0;
    };
}


#endif
