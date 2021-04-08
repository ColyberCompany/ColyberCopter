/**
 * @file MS5611Adapter.cpp
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @date 2021-03-06
 * 
 */

#include "../Sensors/MS5611Adapter.h"


MS5611Adapter::MS5611Adapter(SensorsMediator& sensorsMediator, ITasker& tasker)
    : Sensor(Enums::SensorTypes::BAROMETER, sensorsMediator),
    baro(tasker)
{
}


bool MS5611Adapter::initialize()
{
    int attempts = 0;
    do {
        initResultFlag = baro.initialize();
        attempts++;
    } while (initResultFlag == false && attempts < 3);

    if (isGood())
        baro.setNewReadingEvent(this);

    return initResultFlag;
}


uint16_t MS5611Adapter::startBackgroundCalibration(uint16_t)
{
    // Don't need to calibrate baro
    return 0;
}


const char* MS5611Adapter::getName()
{
    return "MS5611_barometer";
}


void MS5611Adapter::execute()
{
    sensorsMediator.updatePressure(baro.getSmoothPressure());
}
