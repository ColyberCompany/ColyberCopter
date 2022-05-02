/**
 * @file VL53L1XHandler.h
 * @author 
 * @date 2022-04-06
 */

#ifndef VL53L1XHANDLER_h
#define VL53L1XHANDLER_h

#include "Base/Rangefinder.h"
#include <IExecutable.h>
#include <VL53L1X.h>


class VL53L1XHandler : public Rangefinder, public IExecutable
{
    VL53L1X vl53l1x;
    float distance_m = 0;
    VL53L1X::RangeStatus rangeStatus = VL53L1X::RangeStatus::None;

public:
    static const uint32_t UpdatePeriod_us = 100000; // bigger -> more accurate readings

    VL53L1XHandler();

    const char* getName() override {
        return "vl53l1x";
    }

    float getDistance_m() override {
        return distance_m;
    }

    bool isRangeValid() const override {
        return rangeStatus == VL53L1X::RangeStatus::RangeValid;
    }

private:
    bool init_priv() override;
    void execute() override;
};


#endif
