/**
 * @file ControlSticks.h
 * @author Jan Wielgus
 * @brief Class that represents sticks that are on drone remote controller
 * @date 2020-07-31
 * 
 */

#ifndef CONTROLSTICKS_H
#define CONTROLSTICKS_H


class ControlSticks
{
private:
    uint16_t throttle;
    int16_t rotation;
    int16_t tb; // top-back
    int16_t lr; // left-right


public:
    uint16_t getThrottle() const { return throttle; }
    int16_t getRotation() const { return rotation; }
    int16_t getTB() const { return tb; }
    int16_t getLR() const { return lr; }

    void setThrottle(uint16_t value)
    {
        throttle = constrain(value, 0, 1000);
    }
    
    void setRotation(int16_t value)
    {
        rotation = constrain(value, -500, 500);
    }

    void setTB(int16_t value)
    {
        tb = constrain(value, -500, 500);
    }

    void setLR(int16_t value)
    {
        lr = constrain(value, -500, 500);
    }

    void set(uint16_t throttle, int16_t rotation, int16_t tb, int16_t lr)
    {
        setThrottle(throttle);
        setRotation(rotation);
        setTB(tb);
        setLR(lr);
    }
};


#endif
