#ifndef UTILS_H
#define UTILS_H

#include "Vector3.h"

namespace Common
{
    namespace Utils
    {
        template <typename T>
        void printVector3(Stream& serialNumber,const vector3<T>& toShow, const char* separator)
        {
            serialNumber.print(toShow.x);
            serialNumber.print(separator);
            serialNumber.print(toShow.y);
            serialNumber.print(separator);
            serialNumber.println(toShow.z);
        }

        template <typename T>
        void printVector3(Stream& serialNumber,const vector3<T>& toShow, char separator = '\t')
        {
            serialNumber.print(toShow.x);
            serialNumber.print(separator);
            serialNumber.print(toShow.y);
            serialNumber.print(separator);
            serialNumber.println(toShow.z);
        }
    }
}


#endif
