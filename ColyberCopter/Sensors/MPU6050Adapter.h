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
#include "../Common/Vector3.h"
#include <IExecutable.h>
#include <SimpleMPU6050.h>
#include <LowPassFilter.h>


class MPU6050Adapter: public IExecutable
{
    class AccCalib: public Sensor
    {
        MPU6050Adapter& mpuAdapter;

        vector3<int32_t> calibSumVector; // TODO: think how to make that this variables don't occupy memory all the time (they are needed for a short period or never). // Maybe something wih that, that probably always only one sensor will be calibrated at once (also all sensors are calibrated in the simmilar way).
        Counter calibCounter;

    public:
        /**
         * @param sensorsMediator Reference to the sensorsMediator.
         * @param mpu6050 Reference to the mpu6050 instance.
         */
        AccCalib(SensorsMediator& sensorsMediator, MPU6050Adapter& mpuAdapter);

        // initialization is in adapter class
        bool initialize() override;

        /**
         * @brief Runs one calibration loop if sensor need to calibrate
         * (if don't need, this method does nothing).
         * Sensor have to be as horizontal as possible and can't move at all
         * during the calibration process.
         */
        void calibrationLoop();

        uint16_t startBackgroundCalibration(uint16_t amtOfSamples) override;
        FloatAxisVector getOffset() const override;
        void setOffset(FloatAxisVector offset) override;

        const char* getName() override;

        friend class MPU6050Adapter;
    };


    class GyroCalib: public Sensor
    {
        MPU6050Adapter& mpuAdapter;

        vector3<int32_t> calibSumVector; // TODO: think how to make that this variables don't occupy memory all the time (they are needed for a short period or never). // Maybe something wih that, that probably always only one sensor will be calibrated at once (also all sensors are calibrated in the simmilar way).
        Counter calibCounter;

    public:
        /**
         * @param sensorsMediator Reference to the sensorsMediator.
         * @param mpu6050 Reference to the mpu6050 instance.
         */
        GyroCalib(SensorsMediator& sensorsMediator, MPU6050Adapter& mpuAdapter);

        // initialization is in adapter class
        bool initialize() override;

        /**
         * @brief Runs one calibration loop if sensor need to calibrate
         * (if don't need, this method does nothing).
         * Sensor have to be as steady as possible.
         */
        void calibrationLoop();

        uint16_t startBackgroundCalibration(uint16_t amtOfSamples) override;
        FloatAxisVector getOffset() const override;
        void setOffset(FloatAxisVector offset) override;

        const char* getName() override;

        friend class MPU6050Adapter;
    };


private:
    SimpleMPU6050 mpu;

    AccCalib accCalib;
    GyroCalib gyroCalib;

    // Filtering stuff:
    typedef vector3<LowPassFilter<float>> ThreeAxesLPF;
    ThreeAxesLPF accLPF; // accelerometer low-pass filter
    ThreeAxesLPF gyroLPF; // gyro low-pass filter


public:
    MPU6050Adapter(SensorsMediator& sensorsMediator);
    
    void execute() override;
    Sensor* getAccSensor();
    Sensor* getGyroSensor();
    SimpleMPU6050* getMPU6050Ptr();


private:
    void initializeMPU6050IfWasNotInitialized();

    /**
     * @brief Sets parameters for the three axes
     * LowPass filter (the same for all three).
     * @param lpf Three filters struct.
     * @param cutoffFreq Cut-off frequency.
     */
    void config3AxisLPF(ThreeAxesLPF& lpf, float cutoffFreq);
};


#endif
