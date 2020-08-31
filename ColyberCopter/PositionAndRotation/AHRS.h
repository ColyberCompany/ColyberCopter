/**
 * @file AHRS.h
 * @author Jan Wielgus
 * @brief Class that handles all 3D position and rotation calculation.
 * Combine different parts and organize their work.
 * Implements position and rotation interfaces.
 * @date 2020-09-01
 * 
 */

// TODO: design this class in the uml diagram first
// TODO: implement ahrs (h and cpp file)


#ifndef AHRS_H
#define AHRS_H

#include "Interfaces/I3DPosition.h"
#include "Interfaces/I3DRotation.h"
#include <Task.h>
#include "Interfaces/IRotationCalculation.h"
// TODO: maybe position calculation interface will be merged, make according to that


class AHRS : public Interfaces::I3DPosition, public Interfaces::I3DRotation, public Task
{
private:
    Interfaces::IRotationCalculation* rotationCalculation;

public:
    AHRS(Interfaces::IRotationCalculation* rotationCalculation /* other calculation according to change in interface */);

    void execute() override;

    double getLongitude_deg() override;
    double getLatitude_deg() override;
    float getAltitude_m() override;
    float getPitch_deg() override;
    float getRoll_deg() override;
    float getHeading_deg() override;
};


#endif
