/**
 * @file SimpleHMC5883LHandler.cpp
 * @author Jan Wielgus
 * @date 2021-08-12
 */

#include "SimpleHMC5883LHandler.h"


SimpleHMC5883LHandler::SimpleHMC5883LHandler()
{
    // TODO: calibrate magnetometer
    // magnometer().setCalibration(CalibrationMagnetic::Calibration{
    //     .hardIronOffset = ,
    //     .softIronMatrix = 
    // })
}


bool SimpleHMC5883LHandler::init_priv()
{
    return compass.initialize();
}


void SimpleHMC5883LHandler::execute()
{
    compass.readRaw();
}
