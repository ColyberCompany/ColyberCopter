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


namespace Interfaces
{
    class IVirtualPilot
    {
    public:
        virtual ~IVirtualPilot() {}

        virtual bool initializeFlightModes() = 0;
        virtual void runVirtualPilot() = 0;
        virtual bool addFlightMode(FlightMode* flightModeToAdd) = 0;
        virtual bool setFlightMode(Enums::FlightModeTypes flightModeToSet) = 0;
        virtual Enums::FlightModeTypes getCurrentFlightModeType() = 0;
    };
}


#endif
