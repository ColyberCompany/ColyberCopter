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

#include "Interfaces/I3DPosition.h"
#include "Interfaces/I3DRotation.h"
#include <Task.h>
#include "Interfaces/IRotationCalculation.h"
#include "Interfaces/IPositionCalculation.h"


class AHRS : public Interfaces::I3DPosition, public Interfaces::I3DRotation, public Task
{
private:
    Interfaces::IPositionCalculation* positionCalculation;
    Interfaces::IRotationCalculation* rotationCalculation;

public:
    AHRS(Interfaces::IPositionCalculation* positionCalculation, Interfaces::IRotationCalculation* rotationCalculation);

    void execute() override;

    double getLongitude_deg() override;
    double getLatitude_deg() override;
    float getAltitude_m() override;
    float getPitch_deg() override;
    float getRoll_deg() override;
    float getHeading_deg() override;
};


#endif
