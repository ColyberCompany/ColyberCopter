/**
 * @file SimpleHMC5883LHandler.h
 * @author Jan Wielgus
 * @brief Obtaining acc ang gyro readings using SimpleHMC5883L library.
 * @date 2021-08-12
 */

#ifndef SIMPLEHMC5883LHANDLER_H
#define SIMPLEHMC5883LHANDLER_H

#include "Base/Magnetometer.h"
#include "../Common/Vector3.h"
#include <SimpleHMC5883L.h>
#include <IExecutable.h>


class SimpleHMC5883LHandler : public Magnetometer, public IExecutable
{
    SimpleHMC5883L compass;

public:
    SimpleHMC5883LHandler();

    bool initSensor() override;
    const char* getName() override;
    Common::vector3Float get_norm() override;

private:
    void execute() override;
};


#endif

