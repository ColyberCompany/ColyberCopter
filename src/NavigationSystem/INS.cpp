/**
 * @file INS.cpp
 * @author Jan Wielgus
 * @date 2021-08-26
 */

#include "INS.h"
#include "Instances/SensorInstances.h"
#include "Common/Utils.h"
#include "Common/Constants.h"
#include "config.h"

static FusionVector vector3FloatToFusion(const Common::vector3Float& vector3Float);


INS::INS() :
    earthAccOffset(Config::MainFrequency_Hz, 0.02f, 5, 0.05f) // TODO: adjust those values
{
    FusionOffsetInitialise(&fusionOffset, Config::MainFrequency_Hz);
    FusionAhrsInitialise(&fusionAhrs);

    // Set AHRS algorithm settings
    const FusionAhrsSettings settings = { // TODO: test different settings
        .gain = 0.5f,
        .accelerationRejection = 10.0f,
        .magneticRejection = 20.0f,
        .rejectionTimeout = 5 * Config::MainFrequency_Hz, /* 5 seconds */
    };
    FusionAhrsSetSettings(&fusionAhrs, &settings);
}


void INS::execute()
{
    // order is important
    updateAHRS();
    updateAltitude();
    updateLatLong();
}


bool INS::resetAltitude()
{
    if (Instance::baro.isOperating())
    {
        refPressure = Instance::baro.getPressure_hPa();
        return true;
    }

    return false;
}


void INS::updateAHRS()
{
    FusionVector acc = vector3FloatToFusion(Instance::acc.getAcc_norm());
    FusionVector gyro = vector3FloatToFusion(Instance::gyro.getGyro_dps());

    // Update gyroscope offset correction algorithm
    gyro = FusionOffsetUpdate(&fusionOffset, gyro);

    // Update AHRS algorithm
    #ifdef COLYBER_USE_MAGN
    FusionVector magn = vector3FloatToFusion(Instance::magn.getMagn_norm());
    FusionAhrsUpdate(&fusionAhrs, gyro, acc, magn, Config::MainInterval_s);
    #else
    FusionAhrsUpdateNoMagnetometer(&fusionAhrs, gyro, acc, Config::MainInterval_s);
    #endif

    // Update quaternions
    FusionQuaternion fusionQuaternion = FusionAhrsGetQuaternion(&fusionAhrs);
    quaternion.r = fusionQuaternion.element.w;
    quaternion.i = fusionQuaternion.element.x;
    quaternion.j = fusionQuaternion.element.y;
    quaternion.k = fusionQuaternion.element.z;

    // Update Euler angles
    FusionEuler eulerAngles = FusionQuaternionToEuler(fusionQuaternion);
    angles_deg.x = eulerAngles.angle.pitch;
    angles_deg.y = eulerAngles.angle.roll;
    angles_deg.z = eulerAngles.angle.yaw;

    // Update Earth acceleration
    FusionVector fusionEarthAcc = FusionAhrsGetEarthAcceleration(&fusionAhrs);
    earthAcceleration_mps2.x = fusionEarthAcc.axis.x * Common::Consts::GravitationalAcceleration;
    earthAcceleration_mps2.y = fusionEarthAcc.axis.y * Common::Consts::GravitationalAcceleration;
    earthAcceleration_mps2.z = fusionEarthAcc.axis.z * Common::Consts::GravitationalAcceleration;
    earthAcceleration_mps2 = earthAccOffset.update(earthAcceleration_mps2);
}


void INS::updateAltitude()
{
    float curPressure = Instance::baro.getPressure_hPa();
    float curTemperature = Instance::temperature.getTemperature_degC();

    altitude_m = Common::Utils::calculateAltitude(refPressure, curPressure, curTemperature);


// // temp altitude calculation: (instead of Kalman)
//     float baroAlt = Common::Utils::calculateAltitude(refPressure, curPressure, curTemperature);
//     float baroVel = (baroAlt - lastBaroAlt) / Config::MainInterval_s; // derivative
//     lastBaroAlt = baroAlt;

//     verticalVelocity_mps += earthAcceleration_mps2.z * Config::MainInterval_s;
//     verticalVelocity_mps = verticalVelocity_mps * complementaryBeta + baroVel * oneMinusBeta;
//     altitude_m += verticalVelocity_mps * Config::MainInterval_s;
//     altitude_m = altitude_m * complementaryBeta + baroAlt * oneMinusBeta;
//     Serial.print(baroAlt*10);
//     Serial.print('\t');
//     Serial.println(altitude_m*10);
}


void INS::updateLatLong()
{
    // TODO: update latitude and longitude
}




inline FusionVector vector3FloatToFusion(const Common::vector3Float& vector3Float)
{
    return {
        vector3Float.x,
        vector3Float.y,
        vector3Float.z
    };
}
