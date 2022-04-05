/**
 * @file Sensor.h
 * @author Jan Wielgus
 * @brief Base class for all sensor classes.
 * @date 2020-11-25
 * 
 */

#ifndef SENSOR_H
#define SENSOR_H


class Sensor
{
public:
    enum class SensorTypes
    {
        NO_SENSOR,
        ACCELEROMETER,
        GYROSCOPE,
        MAGNETOMETER,
        BAROMETER,
        GPS,
        RANGEFINDER,
        TEMPERATURE_SENSOR
        // new types of sensors goes here...
    };
    
    Sensor(Sensor::SensorTypes _type)
        : type(_type)
    {
        // TODO: maybe add there a sensor instance to the global sensor array (think if such array will be useful eg. for auto initialization)
    }

    Sensor(const Sensor&) = delete; // TODO: make macro to delete copy ctor and copy assignment operator
    Sensor& operator=(const Sensor&) = delete;
    Sensor(Sensor&&) = delete; // TODO: make macro to delete move ctor and move assignment operator
    Sensor& operator=(Sensor&&) = delete;
    
    virtual ~Sensor() {}

    /**
     * @brief Initialize the sensor.
     * @return true if sensor was initialized successfully, false otherwise.
     */
    bool initialize()
    {
        initResult_flag = init_priv();
        return initResult_flag;
    }

    /**
     * @brief Check if sensor was initialized with successful result.
     * @return true if sensor was initialized, false otherwise.
     */
    bool isInitialized() const
    {
        return initResult_flag;
    }

    /**
     * @brief Get type of the current sensor.
     */
    Sensor::SensorTypes getType()
    {
        return type;
    }

    /**
     * @brief Check if sensor is can give good measurements at the moment.
     * @return true if sensor measurements are correct.
     */
    virtual bool isOperating() const
    {
        return initResult_flag; // by default
    }

    /**
     * @brief Name getter of this sensor.
     */
    virtual const char* getName() = 0;


private:
    bool initResult_flag = false;
    const Sensor::SensorTypes type;

    /**
     * @brief Communicate with the sensor and initialze it.
     * @return whether initialization was successful or not.
     */
    virtual bool init_priv() = 0;
};


#endif

