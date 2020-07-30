/**
 * @file I3DPosition.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef I3DPOSITION_H
#define I3DPOSITION_H


namespace Interfaces
{
    class I3DPosition
    {
    public:
        virtual ~I3DPosition() {}

        virtual double getLongitude_deg() = 0;
        virtual double getLatitude_deg() = 0;
        virtual float getAltitude_m() = 0;
    };
}


#endif
