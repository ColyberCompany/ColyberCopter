/**
 * @file NoMotors.h
 * @author Jan Wielgus
 * @date 2021-08-18
 */

#ifndef __NOMOTORS_H__
#define __NOMOTORS_H__

#include "Motors.h"


class NoMotors : public Motors
{
public:
    bool initializeMotors() override
    {
        return true; // TODO: true?
    }

    void setPower(const Common::ControlSticks& stickValues) override
    {
    }
};


#endif // __NOMOTORS_H__
