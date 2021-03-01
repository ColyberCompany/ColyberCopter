/**
 * @file MS5611Adapter.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Adapter for MS5611 barometer.
 * @date 2021-02-25
 * 
 */

#ifndef MS5611ADAPTER_H
#define MS5611ADAPTER_H

#include "Sensor.h"
#include "SensorsMediator.h"
#include "SimpleMS5611Continuous.h"
#include <ITasker.h>
#include <IExecutable.h>


/**
 * @brief Adapter class for MS5611 barometer library.
 * Pressure background measurement begins after initialize() method call.
 */
class MS5611Adapter : public Sensor, private IExecutable
{
    SimpleMS5611Continuous baro;


public:
    MS5611Adapter(SensorsMediator& sensorsMediator, ITasker& tasker)
        : Sensor(sensorsMediator),
        baro(tasker)
    {
    }

    bool initialize() override
    {
        int attempts = 0;
        do {
            initResult = baro.initialize();
            attempts++;
        } while (initResult == false && attempts < 3);

        if (isGood())
            baro.setNewReadingEvent(this);

        return initResult;
    }

    void execute() override
    {
        sensorsMediator.updatePressure(baro.getSmoothPressure());
    }

    uint16_t startBackgroundCalibration(uint16_t) override
    {
        // Don't need to calibrate baro
        return 0;
    }

    FloatAxisVector getOffset() const override
    {
        return FloatAxisVector(0);
    }

    void setOffset(FloatAxisVector) override
    {
    }
};


#endif
