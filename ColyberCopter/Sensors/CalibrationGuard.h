/**
 * @file CalibrationGuard.h
 * @author Jan Wielgus
 * @brief Help to keep track of the sensor calibration process.
 * @date 2020-11-26
 * 
 */

#ifndef CALIBRATIONGUARD_H
#define CALIBRATIONGUARD_H


class CalibrationGuard
{
private:
    uint16_t calibrationLoopsLeft;
    uint16_t calibrationLoopsTotal;

public:
    CalibrationGuard()
    {
        calibrationLoopsLeft = 0;
        calibrationLoopsTotal = 0;
    }

    /**
     * @brief Call each time when start to calibrate.
     * @param calibrationLoops Amount of cycles/loops that the
     * calibration process will take.
     * Decrement each time when isCalibrating() method called.
     */
    void beginCalibrationGuard(uint16_t calibrationLoops)
    {
        calibrationLoopsTotal = calibrationLoops;
        calibrationLoopsLeft = calibrationLoops;
    }

    bool isCalibrating()
    {
        if (calibrationLoopsLeft == 0)
            return false;

        calibrationLoopsLeft--;
        return true;
    }

    /**
     * @brief If isCalibrating() returned true, check if this
     * is the last loop to update calibration values at the end.
     * @return true if this is the last calibration loop
     * (don't use if isCalibrating() returned false).
     */
    bool isLastLoop()
    {
        return calibrationLoopsLeft == 0;
    }

    uint16_t getLoopsTotal()
    {
        return calibrationLoopsTotal;
    }
};


#endif

