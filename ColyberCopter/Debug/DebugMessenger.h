/**
 * @file DebugMessenger.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef DEBUGMESSENGER_H
#define DEBUGMESSENGER_H


class DebugMessenger
{
public:
    virtual ~DebugMessenger() {}

    virtual void enableAndInitialize() = 0;
    virtual void showMessage(const char* message) = 0;
    virtual void showMessage(int num) = 0;
    virtual void showError(int errorCode) = 0;
    virtual void showErrorAndAbort(int errorCode) = 0;
};


#endif
