/**
 * @file I3DRotation.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef I3DROTATION_H
#define I3DROTATION_H


namespace Interfaces
{
    class I3DRotation
    {
    public:
        virtual ~I3DRotation() {}

        virtual float getPitch_deg() = 0;
        virtual float getRoll_deg() = 0;
        virtual float getHeading_deg() = 0;
    };
}


#endif