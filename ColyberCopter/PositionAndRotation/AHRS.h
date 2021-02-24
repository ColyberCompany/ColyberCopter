/**
 * @file AHRS.h
 * @author Jan Wielgus
 * @brief Class that handles all 3D position and rotation calculation.
 * Combine different parts and organize their work.
 * Implements position and rotation interfaces.
 * @date 2020-09-01
 * 
 */

#ifndef AHRS_H
#define AHRS_H

#include "../Interfaces/IAHRS.h"
#include <Task.h>
#include "../Interfaces/IRotationCalculation.h"
#include "../Interfaces/IPositionCalculation.h"


class AHRS : public Interfaces::IAHRS, public Task
{
private:
    Interfaces::IPositionCalculation& positionCalculation;
    Interfaces::IRotationCalculation& rotationCalculation;

public:
    AHRS(Interfaces::IPositionCalculation& _positionCalculation, Interfaces::IRotationCalculation& _rotationCalculation)
        : positionCalculation(_positionCalculation), rotationCalculation(_rotationCalculation)
    {
    }

    void execute() override
    {
        // update rotation calculation first, because position calculation could use rotation
        rotationCalculation.updateRotationCalculation();
        positionCalculation.updatePositionCalculation();
    }

    double getLongitude_deg() override
    {
        return positionCalculation.getLongitude_deg();
    }

    double getLatitude_deg() override
    {
        return positionCalculation.getLatitude_deg();
    }

    float getAltitude_m() override
    {
        return positionCalculation.getAltitude_m();
    }

    float getPitch_deg() override
    {
        return rotationCalculation.getAngles_deg().x;
    }

    float getRoll_deg() override
    {
        return rotationCalculation.getAngles_deg().y;
    }

    float getHeading_deg() override
    {
        return rotationCalculation.getAngles_deg().z;
    }
};


#endif
