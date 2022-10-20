#ifndef W65C02S_ANALYZER_UTILS_H
#define W65C02S_ANALYZER_UTILS_H

#include "Arduino.h"

namespace itsgosho {

    /**
     * Will set the mode of the provided pins to INPUT or OUTPUT
     */
    template<typename T, size_t N>
    void pinModes(T (& pinNumbers)[N], const byte& mode) {
        for (size_t i = 0; i < N; i++) {
            pinMode(pinNumbers[i], mode);
        }
    }

    /**
     * Will read the data from the digital pins and construct a decimal number.
     * The first provided pin is the most significant.
     *
     * Example:
     *
     * Digital Pin(State):
     * 5(1), 3(0), 6(1), 4(1)
     *
     * int pins[4] = {5, 3, 6, 4};
     * digitalRead(pins, MSB); -> 11 (1011)
     */
    template<typename T, size_t N>
    unsigned int digitalReadMSB(T (& pinNumbers)[N]) {

        unsigned int result = 0;

        for (int i = 0; i < N; ++i)
            result = (result << 1) | digitalRead(pinNumbers[i]);

        return result;
    }

    /**
     * Will read the data from the digital pins and construct a decimal number.
     * The last provided pin is the most significant.
     *
     * Example:
     *
     * Digital Pin(State):
     * 5(1), 3(0), 6(1), 4(1)
     *
     * int pins[4] = {5, 3, 6, 4};
     * digitalRead(pins, LSB); -> 13 (1101)
     */
    template<typename T, size_t N>
    unsigned int digitalReadLSB(T (& pinNumbers)[N]) {

        unsigned int result = 0;

        for (int i = N - 1; i >= 0; --i)
            result = (result << 1) | digitalRead(pinNumbers[i]);

        return result;
    }

    /**
     * Will read the data from the digital pins and construct a decimal number.
     * Define the order with the @param bitOrder
     *
     * Example:
     *
     * Digital Pin(State):
     * 5(1), 3(0), 6(1), 4(1)
     *
     * int pins[4] = {5, 3, 6, 4};
     * digitalRead(pins, MSB); -> 11 (1011)
     *
     * int pins[4] = {5, 3, 6, 4};
     * digitalRead(pins, LSB); -> 13 (1101)
     */
    template<typename T, size_t N>
    unsigned int digitalRead(T (& pinNumbers)[N], const bool& bitOrder = MSBFIRST) {

        switch (bitOrder) {
            case LSBFIRST:
                return digitalReadLSB(pinNumbers);
            case MSBFIRST:
                return digitalReadMSB(pinNumbers);
        }
    }
}


#endif //W65C02S_ANALYZER_UTILS_H
