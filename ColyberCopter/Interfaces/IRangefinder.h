/**
 * @file IRangefinder.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IRANGEFINDER_H
#define IRANGEFINDER_H


namespace Interfaces
{
    class IRangefinder
    {
    public:
        virtual ~IRangefinder() {}

        virtual bool initializeRangefinder() = 0;
        virtual float getRangefinderDistance_m() = 0;
    };
}


#endif