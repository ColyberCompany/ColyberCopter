/**
 * @file StreamMedium.h
 * @author Jan Wielgus
 * @brief LoggerMedium for Arduino Stream.
 * @date 2021-08-19
 */

#ifndef __STREAMMEDIUM_H__
#define __STREAMMEDIUM_H__

#include "LogMedium.h"


class StreamMedium : public LogMedium
{
    Stream* stream;

public:
    StreamMedium(Stream* stream)
    {
        this->stream = stream;
    }


    void log(const char* message)
    {
        stream->println(message);
    }
};


#endif // __STREAMMEDIUM_H__
