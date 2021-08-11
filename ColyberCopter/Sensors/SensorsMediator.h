/**
 * @file SensorsMediator.h
 * @author Jan Wielgus
 * @brief This class is used to exchange sensor readings
 * between sensors and rest of the project.
 * @date 2020-11-25
 */


#ifndef SENSORSMEDIATOR_H
#define SENSORSMEDIATOR_H

#include "../Interfaces/ISensorsData.h"


/**
 * @brief Class used to exchange readings values between
 * sensors and other classess.
 * Basically this is class with getters and setters for sensor values
 * and does nothing more than that.
 * Remember that only one sensor should update each measurement!
 */
class SensorsMediator : public Interfaces::ISensorsData
{
    Common::vector3Float accReading;
    Common::vector3Float gyroReading;
    Common::vector3Float magReading;
    float pressureReading;
    double latitude;
    double longitude;
    float bottomRangefinderReading;
    float temperatureReading;

    bool initFlags[18] = {};


public:
    SensorsMediator();
    SensorsMediator(const SensorsMediator&) = delete;
    SensorsMediator& operator=(const SensorsMediator&) = delete;

    Common::vector3Float* getAccReadingHandler();
    Common::vector3Float* getGyroReadingHandler();
    Common::vector3Float* getMagReadingHandler();
    float* getPressureReadingHandler();
    double* getLatitudeReadingHandler();
    double* getLongitudeReadingHandler();
    float* getBottomRangefinderReadingHandler();
    float* getRemperatureReadingHandler();


    // //// \/ \/
    // Interface
    // //// \/ \/

    Common::vector3Float getAcc_normVector() override
    {
        return accReading;
    }
    
    Common::vector3Float getGyro_degPerSec() override
    {
        return gyroReading;
    }

    Common::vector3Float getMag_normVector() override
    {
        return magReading;
    }

    float getPressure_hPa() override
    {
        return pressureReading;
    }

    double getLatitude_deg() override
    {
        return latitude;
    }

    double getLongitude_deg() override
    {
        return longitude;
    }

    float getBottomRangefinderDistance_m() override
    {
        return bottomRangefinderReading;
    }

    float getTemperature_degC() override
    {
        return temperatureReading;
    }


private:
    bool checkInitFlag(uint8_t idx);
};


#endif
