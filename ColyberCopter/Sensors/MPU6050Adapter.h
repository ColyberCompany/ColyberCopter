/**
 * @file MPU6050Adapter.h
 * @author Jan Wielgus
 * @brief Adapter for MPU6050 accelerometer and gyro.
 * @date 2020-11-25
 * 
 */

#ifndef MPU6050ADAPTER_H
#define MPU6050ADAPTER_H

#include "Sensor.h"
#include "SensorsMediator.h"
#include "../Common/Counter.h"
#include "../config.h"
#include <Task.h>
#include <SimpleMPU6050.h>
#include <LowPassFilter.h>


class MPU6050Adapter;
class MPU6050Acc;
class MPU6050Gyro;




class MPU6050Acc: public Sensor
{
private:
    SimpleMPU6050& mpu;

    int32_t sumX; // TODO: think how to make that this variables don't occupy memory all the time (they are needed for a short period or never)
    int32_t sumY; // Maybe something wih that, that probably always only one sensor will be calibrated at once (also all sensors are calibrated in the simmilar way).
    int32_t sumZ;
    Counter calibCounter;
    float deltaTime; // in seconds

public:
    /**
     * @param sensorsMediator Reference to the sensorsMediator.
     * @param mpu6050 Reference to the mpu6050 instance.
     * @param deltaTime Time between next checkCalibration() method calls [in seconds].
     */
    MPU6050Acc(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050, float deltaTime); // TODO: maybe replace delta time in param with config value (used only in cpp)

    MPU6050Acc(const MPU6050Acc&) = delete;
    MPU6050Acc& operator=(const MPU6050Acc&) = delete;

    // initialization is in adapter class
    bool initialize() override;

    /**
     * @brief Sensor have to be as horizontal as possible and don't move at all
     * during the calibration process.
     */
    void checkCalibration();

    uint16_t startBackgroundCalibration(uint16_t amtOfSamples) override;
    FloatAxisVector getOffset() const override;
    void setOffset(FloatAxisVector offset) override;


    friend class MPU6050Adapter;
};





class MPU6050Gyro: public Sensor
{
private:
    SimpleMPU6050& mpu;

    int32_t sumX; // TODO: think how to make that this variables don't occupy memory all the time (they are needed for a short period or never)
    int32_t sumY; // Maybe something wih that, that probably always only one sensor will be calibrated at once (also all sensors are calibrated in the simmilar way).
    int32_t sumZ;
    Counter calibCounter;
    float deltaTime; // in seconds

public:
    /**
     * @param sensorsMediator Reference to the sensorsMediator.
     * @param mpu6050 Reference to the mpu6050 instance.
     * @param deltaTime Time between next checkCalibration() method calls [in seconds].
     */
    MPU6050Gyro(SensorsMediator& sensorsMediator, SimpleMPU6050& mpu6050, float deltaTime);

    MPU6050Gyro(const MPU6050Gyro&) = delete;
    MPU6050Gyro& operator=(const MPU6050Gyro&) = delete;

    // initialization is in adapter class
    bool initialize() override;

    /**
     * @brief Sensor have to don't move at all (can be in any position
     * but as steady as possible).
     */
    void checkCalibration();

    uint16_t startBackgroundCalibration(uint16_t amtOfSamples) override;
    FloatAxisVector getOffset() const override;
    void setOffset(FloatAxisVector offset) override;
    

    friend class MPU6050Adapter;
};






class MPU6050Adapter: public Task
{
private:
    SimpleMPU6050 mpu;
    bool initResult = false;

    MPU6050Acc accClass;
    MPU6050Gyro gyroClass;

    // Low pass filters
    struct ThreeAxisLPF
    {
        LowPassFilter<float> x;
        LowPassFilter<float> y;
        LowPassFilter<float> z;
    };
    ThreeAxisLPF accLPF;
    ThreeAxisLPF gyroLPF;


public:
    MPU6050Adapter(SensorsMediator& sensorsMediator);

    // Call Wire.begin() before!
    bool initialize();
    bool isGood() const;
    void execute() override;
    Sensor* getAccSensor();
    Sensor* getGyroSensor();
    SimpleMPU6050* getMPU6050Ptr();


private:
    /**
     * @brief Sets parameters for the three axis
     * LowPass filter (the same for all three).
     * @param lpf Three filters struct.
     * @param cutoffFreq Cut-off frequency.
     */
    void config3AxisLPF(ThreeAxisLPF& lpf, float cutoffFreq);
};


#endif
