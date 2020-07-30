/**
 * @file IGPS.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef IGPS_H
#define IGPS_H


namespace Interfaces
{
    class IGPS
    {
    public:
        virtual ~IGPS() {}

        virtual bool initializeGPS() = 0;
        virtual double getLatitude_deg() = 0;
        virtual double getLongitude_deg() = 0;
        virtual uint8_t getAmtOfSatellites() = 0;
        virtual bool has3DFix() = 0;
        //TODO: think if there need to be some more methods
    };
}


#endif
