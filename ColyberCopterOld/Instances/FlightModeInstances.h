/**
 * @file FlightModeInstances.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief 
 * @date 2021-03-29
 * 
 */

#ifndef FLIGHTMODEINSTANCES_H
#define FLIGHTMODEINSTANCES_H

#include "../FlightModes/StabilizeFlightMode.h"
#include "../FlightModes/AltHoldFlightMode.h"


namespace Assemble
{
    namespace FlightModes {
        //extern UnarmedFlightMode unarmedFlightMode;
        extern StabilizeFlightMode stabilizeFlightMode;
        extern AltHoldFlightMode altHoldFlightMode;
    }
}

#endif
