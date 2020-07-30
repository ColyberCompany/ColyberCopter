/**
 * @file IDebugMessenger.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IDEBUGMESSENGER_H
#define IDEBUGMESSENGER_H


namespace Interfaces
{
    class IDebugMessenger
    {
    public:
        virtual ~IDebugMessenger() {}

        virtual void initializeDebugMessanger() = 0;
        virtual void showMessage(const char* message) = 0;
        virtual void showErrorAndStop(int errorCode) = 0;
        virtual void showErrorAndContinue(int errorCode) = 0;
    };
}


#endif
