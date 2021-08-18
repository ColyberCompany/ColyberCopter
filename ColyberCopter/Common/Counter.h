/**
 * @file Counter.h
 * @author Jan Wielgus
 * @brief Count down or up from some number.
 * @date 2020-11-26
 * 
 */

#ifndef COUNTER_H
#define COUNTER_H


namespace Common
{
    class Counter
    {
    private:
        uint16_t currentCounter;
        uint16_t initialCounter;

    public:
        Counter()
        {
            reset(0);
        }

        Counter(uint16_t initialValue)
        {
            reset(initialValue);
        }

        /**
         * @brief Set the counter to the specific value.
         */
        void reset(uint16_t initialValue)
        {
            initialCounter = initialValue;
            currentCounter = initialValue;
        }

        /**
         * @brief Get current state of the counter. 
         */
        uint16_t getCurrentCounter() const
        {
            return currentCounter;
        }

        /**
         * @brief Get inial state of the counter
         * (last value set in reset()).
         */
        uint16_t getInitialCounter() const
        {
            return initialCounter;
        }

        /**
         * @brief Decrease the counter value by one
         * (0 is the minimum value).
         */
        void decrement()
        {
            if (currentCounter != 0)
                --currentCounter;
        }

        /**
         * @brief Increase the counter value by one.
         */
        void increment()
        {
            ++currentCounter;
        }
    };
}


#endif
