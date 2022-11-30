#ifndef W65C02S_ANALYZER_STRUCTURES_H
#define W65C02S_ANALYZER_STRUCTURES_H

namespace itsgosho {
    struct MicroprocessorRead {
        bool operation;
        unsigned short int address;
        unsigned short int data;
    };
}

#endif