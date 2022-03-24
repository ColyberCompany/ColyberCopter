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


INS::INS()
{
    FusionBiasInitialise(&fusionBias, 0.5f, Config::MainInterval_s);
    FusionAhrsInitialise(&fusionAhrs, 0.5f); // TODO: test different settings
}


void INS::execute()
{
    // order is important
    updateAHRS();
    udpateAltitude();
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
    auto droneAcc = Instance::acc.get_norm();
    auto droneGyro = Instance::gyro.get_degPerSec();
    FusionVector3 acc = { droneAcc.x, droneAcc.y, droneAcc.z };
    FusionVector3 gyro = { droneGyro.x, droneGyro.y, droneGyro.z };

    // Update gyroscope bias correction algorithm
    gyro = FusionBiasUpdate(&fusionBias, gyro);

    // Update AHRS algorithm
    if (false /* Instance::magn.isOperating() */)
    {
        // TODO: implement this
        // FusionAhrsUpdate(&fusionAhrs, gyro, acc)
    }
    else
    {
        FusionAhrsUpdateWithoutMagnetometer(&fusionAhrs, gyro, acc, Config::MainInterval_s);
    }

    // Update quaternions
    FusionQuaternion fusionQuaternion = FusionAhrsGetQuaternion(&fusionAhrs);
    quaternion.r = fusionQuaternion.element.w;
    quaternion.i = fusionQuaternion.element.x;
    quaternion.j = fusionQuaternion.element.y;
    quaternion.k = fusionQuaternion.element.z;

    // Update Euler angles
    FusionEulerAngles eulerAngles = FusionQuaternionToEulerAngles(fusionQuaternion);
    angles_deg.x = eulerAngles.angle.pitch;
    angles_deg.y = eulerAngles.angle.roll;
    angles_deg.z = eulerAngles.angle.yaw;

    // Update Earth acceleration
    FusionVector3 fusionEarthAcc = FusionAhrsGetEarthAcceleration(&fusionAhrs);
    earthAcceleration_mps2.x = fusionEarthAcc.axis.x * Common::Consts::GravitationalAcceleration;
    earthAcceleration_mps2.y = fusionEarthAcc.axis.y * Common::Consts::GravitationalAcceleration;
    earthAcceleration_mps2.z = fusionEarthAcc.axis.z * Common::Consts::GravitationalAcceleration;
}


void INS::udpateAltitude()
{
    float curPressure = Instance::baro.getPressure_hPa();
    float curTemperature = Instance::temperature.getTemperature_degC();

    altitude_m = Common::Utils::calculateAltitude(refPressure, curPressure, curTemperature);


// // temp altitude calculation: (instead of Kalman)
//     float baroAlt = Common::Utils::calculateAltitude(refPressure, curPressure, curTemperature);
//     float baroVel = (baroAlt - lastBaroAlt) / Config::MainInterval_s; // derivative
//     lastBaroAlt = baroAlt;

//     verticalVelocity_mps += earthAcceleration_mps2.z * Config::MainInterval_s;
//     altitude_m += verticalVelocity_mps * Config::MainInterval_s;

//     float oneMinusBeta = 1.f - complementaryBeta;
//     verticalVelocity_mps = verticalVelocity_mps * complementaryBeta + baroVel * oneMinusBeta;
//     altitude_m = altitude_m * complementaryBeta + baroAlt * oneMinusBeta;
}


void INS::updateLatLong()
{
    // TODO: update latitude and longitude
}
