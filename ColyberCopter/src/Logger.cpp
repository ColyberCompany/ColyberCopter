/**
 * @file Logger.cpp
 * @author Aleksy Walczak (aleksyww@gmail.com)
 * @date 2021-04-10
 */

#include "../Logger/Logger.h"
#include "../Logger/Headers.h"

using Enums::LogType;
using SimpleDataStructures::GrowingArray;
using SimpleDataStructures::ArrayIterator;


void Logger::bind(LogType logType, LogMedium* transmitter)
{
    if (transmitter == nullptr)
        return;

    auto iter = ArrayIterator<Binding>(bindings);
    bool transmitterExists = false;
    while (iter.hasNext())
    {
        auto binding = iter.next();
        if (binding.second == transmitter)
        {
            binding.first = (LogType)(logType | binding.first);
            transmitterExists = true;
        }
    }

    if (!transmitterExists)
        bindings.add(Binding(logType, transmitter));
}


void Logger::unbind(LogType logType, LogMedium* transmitter)
{
    if (transmitter == nullptr)
        return;

    auto iter = ArrayIterator<Binding>(bindings);
    while (iter.hasNext())
    {
        auto binding = iter.next();
        if (binding.second == transmitter)
            binding.first = (LogType)(~logType & binding.first);
    }
}


GrowingArray<LogMedium*> Logger::getLogMediums(LogType logType)
{
    auto iter = ArrayIterator<Binding>(bindings);
    uint8_t n = 0;
    while (iter.hasNext())
        if (iter.next().first == logType) n++;

    auto array = GrowingArray<LogMedium*>(n);

    iter = ArrayIterator<Binding>(bindings);
    while (iter.hasNext())
        array.add(iter.next().second);

    return array;
}


Logger::Logger()
{

}


void Logger::addToBuffer(const char* str)
{
    while(*str != '\0' && endIndex < BufferSize)
    {
        buffer[endIndex++] = *(str++);
    }

    buffer[BufferSize - 1] = '\0'; // TODO: for test to avoid potential errors. Check if \0 is added at the end of message
}


void Logger::addToBuffer(int number)
{
    int n = 0;
    for (int i = 1; number / i; i *= 10)
        n++;

    if (endIndex + n - 1 < BufferSize)
    {
        int j = 1;
        for (int i = 0; i < n; i++)
        {
            buffer[endIndex + n - 1 - i] = ((number / j) % 10) + '0';
            j *= 10;
        }
    }
    else
    {
        while(endIndex < BufferSize)
        {
            buffer[endIndex++] = '*';
        }
    }

    buffer[BufferSize - 1] = '\0'; // TODO: for test to avoid potential errors. Check if \0 is added at the end of message
}


inline void Logger::prepareHeader(LogType logType)
{
    startIndex = LogType::Count;

    LogType type = LogType::Base;
    for (uint8_t i = 0; i < Enums::LogType::Count; i++)
    {
        if (logType & type)
            buffer[--startIndex] = Headers[i];

        type = (LogType)(type*2);
    }
}
