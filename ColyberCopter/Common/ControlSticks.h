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
    int16_t rotation = 0;
    int16_t tb = 0; // top-back
    int16_t lr = 0; // left-right


public:
    /**
     * @brief Return the throttle stick value [0 : 1000].
     */
    uint16_t getThrottle() const { return throttle; }


    /**
     * @brief Return the rotation stick value [-500 : 500]
     */
    int16_t getRotation() const { return rotation; }


    /**
     * @brief Return the top/back stick value [-500 : 500]
     */
    int16_t getTB() const { return tb; }


    /**
     * @brief Return the left/right stick value [-500 : 500]
     */
    int16_t getLR() const { return lr; }


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
     * @brief Set the rotation stick value.
     * Value will be constrained to range from -500 to 500.
     * 
     * @param value Rotation stick value.
     */
    void setRotation(int16_t value)
    {
        rotation = constrain(value, -500, 500);
    }


    /**
     * @brief Set the top/back stick value.
     * Value will be constrained to range from -500 to 500.
     * 
     * @param value Top/back stick value.
     */
    void setTB(int16_t value)
    {
        tb = constrain(value, -500, 500);
    }


    /**
     * @brief Set the left/right stick value.
     * Value will be constrained to range from -500 to 500.
     * 
     * @param value Left/right stick value.
     */
    void setLR(int16_t value)
    {
        lr = constrain(value, -500, 500);
    }


    /**
     * @brief Set all stick values.
     * Throttle value will be constrained to range from 0 to 1000,
     * other sticks to range from -500 to 500.
     * 
     * @param throttle Throttle stick value.
     * @param rotation Rotation stick value.
     * @param tb Top/back stick value.
     * @param lr Left/right stick value.
     */
    void set(uint16_t throttle, int16_t rotation, int16_t tb, int16_t lr)
    {
        setThrottle(throttle);
        setRotation(rotation);
        setTB(tb);
        setLR(lr);
    }
};


#endif
