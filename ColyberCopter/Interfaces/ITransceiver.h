/**
 * @file ITransceiver.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

//TODO: move this whole file to the communication library

#ifndef ITRANSCEIVER_H
#define ITRANSCEIVER_H


namespace Interfaces
{
    class ITransceiver
    {
    public:
        virtual ~ITransceiver() {}

        virtual void begin() = 0;
        virtual bool send(const uint8_t* buffer, size_t size) = 0;
        virtual size_t available() = 0;
        //TODO: create DataBuffer structure in separate file in communication library
        //virtual DataBuffer receiveNextData() = 0;
    };
}


#endif