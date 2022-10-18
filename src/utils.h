#ifndef W65C02S_ANALYZER_UTILS_H
#define W65C02S_ANALYZER_UTILS_H

#include "Arduino.h"

namespace itsgosho {

    /**
     * Will read the data from the digital pins and construct a decimal number.
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
    unsigned long digitalReadMSB(T (& pinNumbers)[N]) {

        long result = 0;

        for (int i = 0; i < N; ++i)
            result = (result << 1) | digitalRead(pinNumbers[i]);

        return result;
    }
}


#endif //W65C02S_ANALYZER_UTILS_H
