/**
 * @file ISensorsChecklist.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef ISENSORSCHECKLIST_H
#define ISENSORSCHECKLIST_H


namespace Interfaces
{
    class ISensorsChecklist
    {
    public:
        virtual ~ISensorsChecklist() {}

        virtual bool isAccelerometerAvailable() = 0;
        virtual bool isGyroscopeAvailable() = 0;
        virtual bool isMangetometerAvailable() = 0;
        virtual bool isBarometerAvailable() = 0;
        virtual bool isGPSAvailable() = 0;
        virtual bool isBottomRangefinderAvailable() = 0;
        virtual bool isTemperatureSensorAvailable() = 0;
    };
}


#endif
