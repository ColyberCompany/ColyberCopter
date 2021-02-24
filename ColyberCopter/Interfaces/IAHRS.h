/**
 * @file IAHRS.h
 * @author Jan Wielgus (jan.wielgus12@gmail.com)
 * @brief Inteface for class that provide all calculated atitude measurements.
 * @date 2021-02-24
 * 
 */

#ifndef IAHRS_H
#define IAHRS_H


namespace Interfaces
{
    class IAHRS
    {
    public:
        virtual ~IAHRS() {}

        virtual float getPitch_deg() = 0;
        virtual float getRoll_deg() = 0;
        virtual float getHeading_deg() = 0;
        //virtual float getYaw_deg() = 0;

        virtual double getLongitude_deg() = 0;
        virtual double getLatitude_deg() = 0;
        virtual float getAltitude_m() = 0;


        // XXX: Return whole vector3 with rotation or position?
    };
}


#endif
