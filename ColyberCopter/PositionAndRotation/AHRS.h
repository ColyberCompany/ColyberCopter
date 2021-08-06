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
#include <IExecutable.h>
#include "../Interfaces/IRotationCalculation.h"
#include "../Interfaces/IPositionCalculation.h"


class AHRS : public Interfaces::IAHRS, public IExecutable
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
        return positionCalculation.getPosition().x;
    }

    double getLatitude_deg() override
    {
        return positionCalculation.getPosition().y;
    }

    float getAltitude_m() override
    {
        return positionCalculation.getPosition().z;
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

    vector3Float getAngles_deg() override
    {
        return rotationCalculation.getAngles_deg();
    }

    vector3Double getPosition() override
    {
        return positionCalculation.getPosition();
    }
};


#endif
