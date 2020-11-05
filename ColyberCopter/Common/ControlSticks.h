/**
 * @file ControlSticks.h
 * @author Jan Wielgus
 * @brief Class that represents sticks that are on drone remote controller.
 * Throttle: 0 : 1000
 * Rotation, TB, LR: -500 : 500
 * @date 2020-07-31
 * 
 */

#ifndef CONTROLSTICKS_H
#define CONTROLSTICKS_H


class ControlSticks
{
private:
    uint16_t throttle = 0;
    int16_t yaw = 0; // heading control
    int16_t pitch = 0; // top-back
    int16_t roll = 0; // left-right


public:
    /**
     * @brief Return the throttle stick value [0 : 1000].
     */
    uint16_t getThrottle() const { return throttle; }


    /**
     * @brief Return the yaw stick value [-500 : 500]
     */
    int16_t getYaw() const { return yaw; }


    /**
     * @brief Return the top/back stick value [-500 : 500]
     */
    int16_t getPitch() const { return pitch; }


    /**
     * @brief Return the left/right stick value [-500 : 500]
     */
    int16_t getRoll() const { return roll; }


    /**
     * @brief Set the throttle stick value.
     * Value will be constrained to range from 0 to 1000.
     * 
     * @param value Throttle stick value.
     */
    void setThrottle(uint16_t value)
    {
        throttle = constrain(value, 0, 1000);
    }
    

    /**
     * @brief Set the yaw stick value (heading control).
     * Value will be constrained to range from -500 to 500.
     * 
     * @param value Rotation stick value.
     */
    void setYaw(int16_t value)
    {
        yaw = constrain(value, -500, 500);
    }


    /**
     * @brief Set the top/back stick value.
     * Value will be constrained to range from -500 to 500.
     * 
     * @param value Top/back stick value.
     */
    void setPitch(int16_t value)
    {
        pitch = constrain(value, -500, 500);
    }


    /**
     * @brief Set the left/right stick value.
     * Value will be constrained to range from -500 to 500.
     * 
     * @param value Left/right stick value.
     */
    void setRoll(int16_t value)
    {
        roll = constrain(value, -500, 500);
    }


    /**
     * @brief Set all stick values.
     * Throttle value will be constrained to range from 0 to 1000,
     * other sticks to range from -500 to 500.
     * 
     * @param throttle Throttle stick value.
     * @param yaw Rotation stick value.
     * @param pitch Top/back stick value.
     * @param roll Left/right stick value.
     */
    void set(uint16_t throttle, int16_t yaw, int16_t pitch, int16_t roll)
    {
        setThrottle(throttle);
        setYaw(yaw);
        setPitch(pitch);
        setRoll(roll);
    }
};


#endif
