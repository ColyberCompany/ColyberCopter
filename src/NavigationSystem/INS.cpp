/**
 * @file INS.cpp
 * @author Jan Wielgus
 * @date 2021-08-26
 */

#include "INS.h"
#include "Instances/SensorInstances.h"
#include "Common/Utils.h"
#include "Common/Constants.h"
#include <cmath>

// TODO: use this calibration
// const FusionMatrix accMisalignment = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
// const FusionVector accSensitivity = {1.0f, 1.0f, 1.0f};
// const FusionVector accOffset = {0.0f, 0.0f, 0.0f};
// const FusionMatrix gyroMisalignment = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
// const FusionVector gyroSensitivity = {1.0f, 1.0f, 1.0f};
// const FusionVector gyroOffset = {0.0f, 0.0f, 0.0f};
// const FusionMatrix softIronMatrix = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
// const FusionVector hardIronOffset = {0.0f, 0.0f, 0.0f};

static FusionVector vector3FloatToFusion(const Common::vector3Float& vector3Float);


INS::INS()
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


bool INS::resetBaroAltitude()
{
    if (!Instance::baro.isOperating())
        return false;

    refPressure = Instance::baro.getPressure_hPa();
    return true;

}


void INS::updateAHRS()
{
    FusionVector acc = vector3FloatToFusion(Instance::acc.getAcc_norm());
    FusionVector gyro = vector3FloatToFusion(Instance::gyro.getGyro_dps());

    // Apply calibration 
    // acc = FusionCalibrationInertial(acc, accMisalignment, accSensitivity, accOffset);  // TODO: use this calibration (maybe not here, but in a sensor handler)
    // gyro = FusionCalibrationInertial(gyro, gyroMisalignment, gyroSensitivity, gyroOffset);  // TODO: use this calibration (maybe not here, but in a sensor handler)

    // Update gyroscope offset correction algorithm
    gyro = FusionOffsetUpdate(&fusionOffset, gyro);

    // Update AHRS algorithm
    #ifdef COLYBER_USE_MAGN
    FusionVector magn = vector3FloatToFusion(Instance::magn.getMagn_norm());
    // magn = FusionCalibrationMagnetic(magn, softIronMatrix, hardIronOffset); // TODO: use this calibration (maybe not here, but in a sensor handler)
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
}


void INS::updateAltitude()
{
    static const float MinRangefinderTiltCompMultiplayer = cosf(Config::MaxRfdrTiltCorrectionAngle_rad);
    using Instance::btmRangefinder;

    float curPressure = Instance::baro.getPressure_hPa();
    float curTemperature = Instance::temperature.getTemperature_degC();

    float baroAltitude_m = Common::Utils::calculateAltitude(refPressure, curPressure, curTemperature);

    #ifdef COLYBER_USE_BTM_RANGEFINDER
    // Baro and rangefinder altitude fusion (use rangefinder always when available)
    auto angles_rad = getAngles_rad();
    float tiltCompMult = cosf(angles_rad.x) * cosf(angles_rad.y);
    if (btmRangefinder.isRangeValid() && tiltCompMult > MinRangefinderTiltCompMultiplayer)
    {
        // compensate rangefinder measurement with vehicle tilt angle
        float heightRangefinder_m = Instance::btmRangefinder.getDistance_m() * tiltCompMult;

        baroRangefinderAltDiff = heightRangefinder_m - baroAltitude_m;
        altitude_m = heightRangefinder_m;
    }
    else
    {
        altitude_m = baroAltitude_m + baroRangefinderAltDiff;
    }
    altitude_m = rangefinderHeightFilter.update(altitude_m); // TODO: smooth value in better way
    #else // baro only
    altitude_m = baroAltitude_m;
    #endif // COLYBER_USE_BTM_RANGEFINDER


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




inline FusionVector vector3FloatToFusion(const Common::vector3Float& vector3Float)
{
    return {
        vector3Float.x,
        vector3Float.y,
        vector3Float.z
    };
}
