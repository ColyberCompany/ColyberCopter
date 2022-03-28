/**
 * @file INS.cpp
 * @author Jan Wielgus
 * @date 2021-08-26
 */

#include "INS.h"
#include "Instances/SensorInstances.h"
#include "Common/Utils.h"
#include "config.h"


INS::INS()
    : ahrs(Config::MainInterval_s)
{
}


void INS::execute()
{
    // order is important
    updateQuaternion();
    updateAngles();
    updateEarthAcceleration();
    udpateAltitude();
    updateLatLong();
}


bool INS::resetAltitude()
{
    bool isBaroOperating = Instance::baro.isOperating();
    if (isBaroOperating)
        refPressure = Instance::baro.getPressure_hPa();

    return isBaroOperating;
}


void INS::updateQuaternion()
{
    MadgwickAHRS::Quaternion q;
    auto acc = Instance::acc.get_norm();
    auto gyro = Instance::gyro.get_radPerSec();

    if (Instance::magn.isOperating())
    {
        auto magn = Instance::magn.get_norm();

        q = ahrs.madgwickAHRSUpdate(
            gyro.x, gyro.y, gyro.z,
            acc.x, acc.y, acc.z,
            magn.x, magn.y, magn.z
        );
    }
    else
    {
        q = ahrs.madgwickAHRSUpdateIMU(
            gyro.x, gyro.y, gyro.z,
            acc.x, acc.y, acc.z
        );
    }

    quaternion = {q.r, q.i, q.j, q.k};
}


void INS::updateAngles()
{
#define q0 quaternion.r
#define q1 quaternion.i
#define q2 quaternion.j
#define q3 quaternion.k
    angles_rad.y = atan2f(q0 * q1 + q2 * q3, 0.5f - q1 * q1 - q2 * q2);		// roll
    angles_rad.x = asinf(-2.0f * (q1 * q3 - q0 * q2));						// pitch
    angles_rad.z = atan2f(q1 * q2 + q0 * q3, 0.5f - q2 * q2 - q3 * q3);		// roll (heading)
#undef q0
#undef q1
#undef q2
#undef q3
}


void INS::updateEarthAcceleration()
{
    using Common::Consts::GravitationalAcceleration;

    auto acc = Instance::acc.get_norm();
    earthAcceleration_mps2 = quaternion.rotate3DVector(acc);
    earthAcceleration_mps2 = {
        earthAcceleration_mps2.x * GravitationalAcceleration,
        earthAcceleration_mps2.y * GravitationalAcceleration,
        (earthAcceleration_mps2.z - 1.f) * GravitationalAcceleration
    };
}


void INS::udpateAltitude()
{
    float curPressure = Instance::baro.getPressure_hPa();
    float curTemperature = Instance::temperature.getTemperature_degC();

    // altitude_m = Common::Utils::calculateAltitude(refPressure, curPressure, curTemperature);


// // temp altitude calculation: (instead of Kalman)
    float baroAlt = Common::Utils::calculateAltitude(refPressure, curPressure, curTemperature);
    float baroVel = (baroAlt - lastBaroAlt) / Config::MainInterval_s; // derivative
    lastBaroAlt = baroAlt;

    verticalVelocity_mps += earthAcceleration_mps2.z * Config::MainInterval_s;
    altitude_m += verticalVelocity_mps * Config::MainInterval_s;

    float oneMinusBeta = 1.f - complementaryBeta;
    verticalVelocity_mps = verticalVelocity_mps * complementaryBeta + baroVel * oneMinusBeta;
    altitude_m = altitude_m * complementaryBeta + baroAlt * oneMinusBeta;
}


void INS::updateLatLong()
{
    // TODO: update latitude and longitude
}
