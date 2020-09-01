/**
 * @file IFailsafe.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IFAILSAFE_H
#define IFAILSAFE_H

#include <IExecutable.h>


namespace Interfaces
{
    class IFailsafe
    {
    public:
        virtual ~IFailsafe() {}

        virtual bool initializeFailsafe() = 0;
        virtual void addFailsafeEvent(IExecutable* failsafeEvent) = 0;
        virtual void removeFailsafeEvent(IExecutable* failsafeEvent) = 0;
        virtual void runFailsafeCheckLoop() = 0;
    };
}


#endif
