/**
 * @file IVirtualPilot.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */


#ifndef IVIRTUALPILOT_H
#define IVIRTUALPILOT_H


namespace Interfaces
{
    class IVirtualPilot
    {
    public:
        virtual ~IVirtualPilot() {}

        virtual bool initializeFlightModes() = 0;
        virtual void runVirtualPilot() = 0;
        //TODO: create flight mode class and flight mode types enum and finish this interface
    };
}


#endif
