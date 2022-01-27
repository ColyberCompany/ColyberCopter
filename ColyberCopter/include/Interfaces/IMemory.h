/**
 * @file IMemory.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IMEMORY_H
#define IMEMORY_H


namespace Interfaces
{
    class IMemory
    {
    public:
        virtual ~IMemory() {}

        virtual void initializeMemory() = 0;
        virtual size_t getMemorySize_bytes() = 0;
        virtual void clear() = 0;
        virtual bool isGood() = 0; // TODO: figure out better name for this method
        virtual uint8_t read_uint8_t(size_t location) = 0;
        virtual uint8_t read_uint16_t(size_t location) = 0;
        virtual uint8_t read_uint32_t(size_t location) = 0;
        virtual bool save_uint8_t(size_t location, uint8_t value) = 0;
        virtual bool save_uint16_t(size_t location, uint16_t value) = 0;
        virtual bool save_uint32_t(size_t location, uint32_t value) = 0;
    };
}


#endif
