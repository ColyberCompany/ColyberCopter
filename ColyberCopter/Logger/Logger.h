/**
 * @file Logger.h
 * @author Aleksy Walczak (aleksyww@gmail.com)
 * @date 2021-04-09
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "Headers.h"
#include "LogMedium.h"
#include "../Common/Pair.h"
#include "../Enums/LogType.h"
#include "../config.h"
#include <GrowingArray.h>
#include <ArrayIterator.h>


class Logger
{
    typedef Pair<Enums::LogType, LogMedium*> Binding;

    SimpleDataStructures::GrowingArray<Binding> bindings;

    static constexpr size_t BufferSize = Config::MaxLogSize + Enums::LogType::Count + 1;
    char buffer[BufferSize];
    uint8_t startIndex;
    uint8_t endIndex = Enums::LogType::Count + 1;


public:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void bind(Enums::LogType logType, LogMedium* transmitter);
    void unbind(Enums::LogType logType, LogMedium* transmitter);
    SimpleDataStructures::GrowingArray<LogMedium*> getLogMediums(Enums::LogType logType);

    template <class First, class... Args>
    void error(First first, Args... args);

    template <class First, class... Args>
    void debug(First first, Args... args);

    template <class First, class... Args>
    void info(First first, Args... args);

private:
    void addToBuffer(const char* str);
    void addToBuffer(int number);

    void prepareHeader(Enums::LogType logType);

    template <class T>
    void log(Enums::LogType logType, T item);

    template <class First, class... Args>
    void log(Enums::LogType logType, First first, Args... args);
};


template <class T>
void Logger::log(Enums::LogType logType, T item)
{
    using SimpleDataStructures::ArrayIterator;

    addToBuffer(item);

    auto iter = ArrayIterator<Binding>(bindings);
    while (iter.hasNext())
    {
        auto binding = iter.next();
        if (binding.first & logType)
        {
            prepareHeader((Enums::LogType)(logType & binding.first));
            binding.second->log(buffer + startIndex);
        }
    }

    endIndex = Enums::LogType::Count + 1;
}


template<class First, class... Args>
void Logger::log(Enums::LogType logType, First first, Args... args)
{
    addToBuffer(first);
    log(logType, args...);
}


template <class First, class... Args>
void Logger::error(First first, Args... args)
{
    log(Enums::LogType::Error | Enums::LogType::Base, first, args...);
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
