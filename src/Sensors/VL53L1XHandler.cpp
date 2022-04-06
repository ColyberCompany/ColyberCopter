/**
 * @file VL53L1XHandler.cpp
 * @author Jan Wielgus
 * @date 2022-04-06
 */

#include "VL53L1XHandler.h"


VL53L1XHandler::VL53L1XHandler()
{
}


bool VL53L1XHandler::init_priv()
{
    // call Wire.begin() and set 400kHz clock outside

    if (!vl53l1x.init())
        return false;

    vl53l1x.setDistanceMode(VL53L1X::DistanceMode::Long);
    vl53l1x.setMeasurementTimingBudget(UpdatePeriod_us);

    vl53l1x.startContinuous(UpdatePeriod_us / 1000);

    return true;
}


void VL53L1XHandler::execute()
{
    distance_m = vl53l1x.read(false) * 0.001f;
}
