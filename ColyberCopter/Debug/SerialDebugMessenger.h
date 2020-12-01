/**
 * @file SerialDebugMessenger.h
 * @author Jan Wielgus
 * @brief 
 * @date 2020-12-01
 * 
 */

#ifndef SERIALDEBUGMESSENGER_H
#define SERIALDEBUGMESSENGER_H

#include "DebugMessenger.h"
#include "Enums/BaudRateTypes.h"


class SerialDebugMessenger: public DebugMessenger
{
private:
    bool initializedFlag = false;
    HardwareSerial& serial;

    const char* MessagePrefix = "DMsg: ";

public:
    SerialDebugMessenger(HardwareSerial& hardwareSerial)
        : serial(hardwareSerial)
    {
    }

    void enableAndInitialize() override
    {
        initializedFlag = true;
        serial.begin(Enums::BaudRateTypes::BAUD_115200);
        serial.println("Debugging was enabled.");
        delay(4);
    }

    void showMessage(const char* message) override
    {
        serial.print(MessagePrefix);
        serial.println(message);
    }

    void showMessage(int num) override
    {
        serial.print(MessagePrefix);
        serial.println(num);
    }

    void showError(int errorCode) override
    {
        serial.print("ERROR! Code: ");
        serial.println(errorCode);
    }

    void showErrorAndAbort(int errorCode) override
    {
        showError(errorCode);
        serial.println("PROGRAM IS ABORTED!");
        while (true);
    }
};


#endif

