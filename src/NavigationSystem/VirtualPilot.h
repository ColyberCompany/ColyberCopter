/**
 * @file VirtualPilot.h
 * @author Jan Wielgus
 * @brief VirtualPilot is the class that handles changing flight modes and
 * transmits control values to the motors.
 * @date 2020-11-09
 * 
 */

#ifndef VIRTUALPILOT_H
#define VIRTUALPILOT_H

#include "Interfaces/IVirtualPilot.h"
#include "FlightModes/FlightMode.h"
#include "config.h"
#include <IExecutable.h>
#include <GrowingArray.h>
#include <AverageFilter.h>


class VirtualPilot : public Interfaces::IVirtualPilot, public IExecutable
{
private:
    FlightMode* currentFlightMode;
    SimpleDataStructures::GrowingArray<FlightMode*> flightModesArray;

    // average filters for lower frequency pilot sticks values
    static constexpr uint8_t StickSamplesToAverage =
        Config::MainFrequency_Hz / (float)Config::RmtCtrlReceivingFrequency_Hz + 0.5f; // <main freq> / <stick value receiving freq> : 250/30
    FL::AverageFilter<uint16_t, StickSamplesToAverage> throttleStickAverage;
    FL::AverageFilter<int16_t, StickSamplesToAverage> yawStickAverage;
    FL::AverageFilter<int16_t, StickSamplesToAverage> pitchStickAverage;
    FL::AverageFilter<int16_t, StickSamplesToAverage> rollStickAverage;

public:
    VirtualPilot(FlightMode& initialFlightMode);

    bool addFlightMode(FlightMode* flightMode) override;
    bool initializeFlightModes() override;
    bool setFlightMode(FlightMode::FlightModeTypes flightModeToSetType) override;
    void runVirtualPilot() override;
    FlightMode::FlightModeTypes getCurrentFlightModeType() override;

    void execute() override;


private:
    /**
     * @brief Get flight mode pointer from list of previously added ones by the type.
     * @param flightModeType Type of flight mode to add.
     * @return Pointer to the flight mode (previously added by addFlightMode() method)
     * or nullptr if flight mode of that type was not found.
     */
    FlightMode* getFlightModePtrByType(FlightMode::FlightModeTypes flightModeType);

    /**
     * @brief Execute prepare() method for flight modes on the list that wasn't used and now will be
     * and leave() method for flight modes that was used but now won't be.
     * @param oldFlightMode flight mode that was previously set.
     * @param newFlightMode flight mode that will be set from now.
     */
    void executePrepareAndLeaveMethods(const FlightMode* oldFlightMode, const FlightMode* newFlightMode);
};


#endif

