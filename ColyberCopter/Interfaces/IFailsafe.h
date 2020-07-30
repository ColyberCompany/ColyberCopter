/**
 * @file IFailsafe.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IFAILSAFE_H
#define IFAILSAFE_H


namespace Interfaces
{
    class IFailsafe
    {
    public:
        virtual ~IFailsafe() {}

        virtual bool initializeFailsafe() = 0;

        // TODO: add IExecutable interface first (in Tasker library)
        //virtual void addFailsafeEvent(...)
        //virtual void removeFailsafeEvent(...)

        virtual void runFailsafeCheckLoop() = 0;
    };
}


#endif
