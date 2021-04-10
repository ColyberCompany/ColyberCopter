/**
 * @file Logger.h
 * @author Aleksy Walczak (aleksyww@gmail.com)
 * @date 2021-04-09
 * 
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "../Common/Pair.h"
#include "../Enums/LogType.h"
#include <DataBuffer.h>
#include <GrowingArray.h>
#include <ITransmitter.h>


class Logger
{
    ExtendedDataBuffer buffer;
    GrowingArray<Pair<Enums::LogType, ITransmitter*>> bindings;

    void log(Enums::LogType logType, const char* str);
    void log(Enums::LogType logType, int i);

    template <class First, class... Args>
    void log(Enums::LogType logType, First first, Args... args);

public:
    void setTransmitter(Enums::LogType logType, ITransmitter* transmitter);
    ITransmitter* getTransmitter(Enums::LogType logType);

    template <class First, class... Args>
    void error(First first, Args... args);

    template <class First, class... Args>
    void debug(First first, Args... args);

    template <class First, class... Args>
    void info(First first, Args... args);
};


template<class First, class... Args>
void Logger::log(Enums::LogType logType, First first, Args... args)
{
    log(logType, first);
    log(logType, args...);
}


template <class First, class... Args>
void Logger::error(First first, Args... args)
{
    log(Enums::LogType::Error | Enums::LogType::Debug | Enums::LogType::Info | Enums::LogType::Base, first, args...);
}


template <class First, class... Args>
void Logger::debug(First first, Args... args)
{
    log(Enums::LogType::Debug | Enums::LogType::Base, first, args...);
}


template <class First, class... Args>
void Logger::info(First first, Args... args)
{
    log(Enums::LogType::Info | Enums::LogType::Base, first, args...);
}


#endif
