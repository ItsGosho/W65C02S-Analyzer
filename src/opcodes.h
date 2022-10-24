#ifndef W65C02S_ANALYZER_OPCODES_H
#define W65C02S_ANALYZER_OPCODES_H

#include "Arduino.h"

namespace itsgosho {

    enum AddressMode {
        ABSOLUTE,                          // a
        ABSOLUTE_INDEXED_INDIRECT,         // (a,x)
        ABSOLUTE_INDEXED_WITH_X,           // a,x
        ABSOLUTE_INDEXED_WITH_Y,           // a,y
        ABSOLUTE_INDIRECT,               // (a)
        ACCUMULATOR,                       // A
        IMMEDIATE,                         // #
        IMPLIED,                           // i
        PROGRAM_COUNTER_RELATIVE,          // r
        STACK,                             // s
        ZERO_PAGE,                         // zp
        ZERO_PAGE_INDEXED_INDIRECT,        // (zp,x)
        ZERO_PAGE_INDEXED_WITH_X,          // zp,x
        ZERO_PAGE_INDEXED_WITH_Y,          // zp,y
        ZERO_PAGE_INDIRECT,                // (zp)
        ZERO_PAGE_INDIRECT_INDEXED_WITH_Y  // (zp),y
    };

    enum OpCode {
        ADC_,
        AND,
        ASL,
        BBR0,
        BBR1,
        BBR2,
        BBR3,
        BBR4,
        BBR5,
        BBR6,
        BBR7,
        BBS0,
        BBS1,
        BBS2,
        BBS3,
        BBS4,
        BBS5,
        BBS6,
        BBS7,
        BCC,
        BCS,
        BEQ,
        BIT,
        BMI,
        BNE,
        BPL,
        BRA,
        BRK,
        BVC,
        BVS,
        CLC,
        CLD,
        CLI,
        CLV,
        CMP,
        CPX,
        CPY,
        DEC_,
        DEX,
        DEY,
        EOR,
        INC,
        INX,
        INY,
        JMP,
        JSR,
        LDA,
        LDX,
        LDY,
        LSR,
        NOP,
        ORA,
        PHA,
        PHP,
        PHX,
        PHY,
        PLA,
        PLP,
        PLX,
        PLY,
        RMB0,
        RMB1,
        RMB2,
        RMB3,
        RMB4,
        RMB5,
        RMB6,
        RMB7,
        ROL,
        ROR,
        RTI,
        RTS,
        SBC,
        SEC,
        SED,
        SEI,
        SMB0,
        SMB1,
        SMB2,
        SMB3,
        SMB4,
        SMB5,
        SMB6,
        SMB7,
        STA,
        STP,
        STX,
        STY,
        STZ,
        TAX,
        TAY,
        TRB,
        TSB,
        TSX,
        TXA,
        TXS,
        TYA,
        WAI,
    };

    struct OpCodeAddress {
        OpCode opCode;
        AddressMode addressMode;
        bool hasOpCode;

        OpCodeAddress() : hasOpCode(false) {
        }

        OpCodeAddress(OpCode opCode, AddressMode addressMode)
                : opCode(opCode), addressMode(addressMode), hasOpCode(true) {
        }
    };


    /**
     * Each opcode has unique address.
     * For example 0xEA - NOP
     * https://www.westerndesigncenter.com/wdc/documentation/w65c02s.pdf : Page: 22
     * Some opcodes appear twice. That is because there is different addressing type for each of them. Page: 20
     * The array is used to visualize what opcode was read from the bus.
     */
    static OpCodeAddress opCodeAddresses[0xFF + 1] = {
            /*0x0*/
            {OpCode::BRK,  AddressMode::STACK},                             //0x00 s
            {OpCode::ORA,  AddressMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x01 (zp,x)
            {},                                                                                 //0x02
            {},                                                                                 //0x03
            {OpCode::TSB,  AddressMode::ZERO_PAGE},                         //0x04 zp
            {OpCode::ORA,  AddressMode::ZERO_PAGE},                         //0x05 zp
            {OpCode::ASL,  AddressMode::ZERO_PAGE},                         //0x06 zp
            {OpCode::RMB0, AddressMode::ZERO_PAGE},                         //0x07 zp
            {OpCode::PHP,  AddressMode::STACK},                             //0x08 s
            {OpCode::ORA,  AddressMode::IMMEDIATE},                         //0x09 #
            {OpCode::ASL,  AddressMode::ACCUMULATOR},                       //0x0A A
            {},                                                                                 //0x0B
            {OpCode::TSB,  AddressMode::ABSOLUTE},                          //0x0C a
            {OpCode::ORA,  AddressMode::ABSOLUTE},                          //0x0D a
            {OpCode::ASL,  AddressMode::ABSOLUTE},                          //0x0E a
            {OpCode::BBR0, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x0F r
            /*0x1*/
            {OpCode::BPL,  AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x10 r
            {OpCode::ORA,  AddressMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x11 (zp),y
            {OpCode::ORA,  AddressMode::ZERO_PAGE_INDIRECT},                //0x12 (zp)
            {},                                                                                 //0x13
            {OpCode::TRB,  AddressMode::ZERO_PAGE},                         //0x14 zp
            {OpCode::ORA,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x15 zp,x
            {OpCode::ASL,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x16 zp,x
            {OpCode::RMB1, AddressMode::ZERO_PAGE},                         //0x17 zp
            {OpCode::CLC,  AddressMode::IMPLIED},                           //0x18 i
            {OpCode::ORA,  AddressMode::ABSOLUTE_INDEXED_WITH_Y},           //0x19 a,y
            {OpCode::INC,  AddressMode::ACCUMULATOR},                       //0x1A A
            {},                                                                                 //0x1B
            {OpCode::TRB,  AddressMode::ABSOLUTE},                          //0x1C a
            {OpCode::ORA,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x1D a,x
            {OpCode::ASL,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x1E a,x
            {OpCode::BBR1, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x1F r
            /*0x2*/
            {OpCode::JSR,  AddressMode::ABSOLUTE},                          //0x20 a
            {OpCode::AND,  AddressMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x21 (zp),y
            {},                                                                                 //0x22
            {},                                                                                 //0x23
            {OpCode::BIT,  AddressMode::ZERO_PAGE},                         //0x24 zp
            {OpCode::AND,  AddressMode::ZERO_PAGE},                         //0x25 zp
            {OpCode::ROL,  AddressMode::ZERO_PAGE},                         //0x26 zp
            {OpCode::RMB2, AddressMode::ZERO_PAGE},                         //0x27 zp
            {OpCode::PLP,  AddressMode::STACK},                             //0x28 s
            {OpCode::AND,  AddressMode::IMMEDIATE},                         //0x29 #
            {OpCode::ROL,  AddressMode::ACCUMULATOR},                       //0x2A A
            {},                                                                                 //0x2B
            {OpCode::BIT,  AddressMode::ABSOLUTE},                          //0x2C a
            {OpCode::AND,  AddressMode::ABSOLUTE},                          //0x2D a
            {OpCode::ROL,  AddressMode::ABSOLUTE},                          //0x2E a
            {OpCode::BBR2, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x2F r
            /*0x3*/
            {OpCode::BMI,  AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x30 r
            {OpCode::AND,  AddressMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x31 (zp),y
            {OpCode::AND,  AddressMode::ZERO_PAGE_INDIRECT},                //0x32 (zp)
            {},                                                                                 //0x33
            {OpCode::BIT,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x34 zp,x
            {OpCode::AND,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x35 zp,x
            {OpCode::ROL,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x36 zp,x
            {OpCode::RMB3, AddressMode::ZERO_PAGE},                         //0x37 zp
            {OpCode::SEC,  AddressMode::IMPLIED},                           //0x38 I
            {OpCode::AND,  AddressMode::ABSOLUTE_INDEXED_WITH_Y},           //0x39 a,y
            {OpCode::DEC_, AddressMode::ACCUMULATOR},                       //0x3A A*
            {},                                                                                 //0x3B
            {OpCode::BIT,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x3C a,x
            {OpCode::AND,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x3D a,x
            {OpCode::ROL,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x3E a,x
            {OpCode::BBR2, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x3F r
            /*0x4*/
            {OpCode::RTI,  AddressMode::STACK},                             //0x40 s
            {OpCode::EOR,  AddressMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x41 (zp,x)
            {},                                                                                 //0x42
            {},                                                                                 //0x43
            {},                                                                                 //0x44
            {OpCode::EOR,  AddressMode::ZERO_PAGE},                         //0x45 zp
            {OpCode::LSR,  AddressMode::ZERO_PAGE},                         //0x46 zp
            {OpCode::RMB4, AddressMode::ZERO_PAGE},                         //0x47 zp
            {OpCode::PHA,  AddressMode::STACK},                             //0x48 s
            {OpCode::EOR,  AddressMode::IMMEDIATE},                         //0x49 #
            {OpCode::LSR,  AddressMode::ACCUMULATOR},                       //0x4A A
            {},                                                                                 //0x4B
            {OpCode::JMP,  AddressMode::ABSOLUTE},                          //0x4C a
            {OpCode::EOR,  AddressMode::ABSOLUTE},                          //0x4D a
            {OpCode::LSR,  AddressMode::ABSOLUTE},                          //0x4E a
            {OpCode::BBR4, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x4F r
            /*0x5*/
            {OpCode::BVC,  AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x50 r
            {OpCode::EOR,  AddressMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x51 (zp),y
            {OpCode::EOR,  AddressMode::ZERO_PAGE},                         //0x52 (zp)
            {},                                                                                 //0x53
            {},                                                                                 //0x54
            {OpCode::EOR,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x55 zp,x
            {OpCode::LSR,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x56 zp,x
            {OpCode::RMB5, AddressMode::ZERO_PAGE},                         //0x57 zp
            {OpCode::CLI,  AddressMode::IMPLIED},                           //0x58 i
            {OpCode::EOR,  AddressMode::ABSOLUTE_INDEXED_WITH_Y},           //0x59 a,y
            {OpCode::PHY,  AddressMode::STACK},                             //0x5A s
            {},                                                                                 //0x5B
            {},                                                                                 //0x5C
            {OpCode::EOR,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x5D a,x
            {OpCode::LSR,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x5E a,x
            {OpCode::BBR5, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x5F r
            /*0x6*/
            {OpCode::RTS,  AddressMode::STACK},                             //0x60 s
            {OpCode::ADC_, AddressMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x61 (zp,x)
            {},                                                                                 //0x62
            {},                                                                                 //0x63
            {OpCode::STZ,  AddressMode::ZERO_PAGE},                         //0x64 zp
            {OpCode::ADC_, AddressMode::ZERO_PAGE},                         //0x65 zp
            {OpCode::ROR,  AddressMode::ZERO_PAGE},                         //0x66 zp
            {OpCode::RMB6, AddressMode::ZERO_PAGE},                         //0x67 zp
            {OpCode::PLA,  AddressMode::STACK},                             //0x68 s
            {OpCode::ADC_, AddressMode::IMMEDIATE},                         //0x69 #
            {OpCode::ROR,  AddressMode::ACCUMULATOR},                       //0x6A A
            {},                                                                                 //0x6B
            {OpCode::JMP,  AddressMode::ABSOLUTE_INDIRECT},                 //0x6C (a)
            {OpCode::ADC_, AddressMode::ABSOLUTE},                          //0x6D a
            {OpCode::ROR,  AddressMode::ABSOLUTE},                          //0x6E a
            {OpCode::BBR6, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x6F r
            /*0x7*/
            {OpCode::BVS,  AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x70 r
            {OpCode::ADC_, AddressMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x71 (zp),y
            {OpCode::ADC_, AddressMode::ZERO_PAGE_INDIRECT},                //0x72 (zp)
            {},                                                                                 //0x73
            {OpCode::STZ,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x74 zp,x
            {OpCode::ADC_, AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x75 zp,x
            {OpCode::ROR,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x76 zp,x
            {OpCode::RMB7, AddressMode::ZERO_PAGE},                         //0x77 zp
            {OpCode::SEI,  AddressMode::IMPLIED},                           //0x78 i
            {OpCode::ADC_, AddressMode::ABSOLUTE_INDEXED_WITH_Y},           //0x79 a,y
            {OpCode::PLY,  AddressMode::STACK},                             //0x7A s
            {},                                                                                 //0x7B
            {OpCode::JMP,  AddressMode::ABSOLUTE_INDEXED_INDIRECT},         //0x7C (a,x)
            {OpCode::ADC_, AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x7D a,x
            {OpCode::ROR,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x7E a,x
            {OpCode::BBR7, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x7F r
            /*0x8*/
            {OpCode::BRA,  AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x80 r
            {OpCode::STA,  AddressMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x81 (zp,x)
            {},                                                                                 //0x82
            {},                                                                                 //0x83
            {OpCode::STY,  AddressMode::ZERO_PAGE},                         //0x84 zp
            {OpCode::STA,  AddressMode::ZERO_PAGE},                         //0x85 zp
            {OpCode::STX,  AddressMode::ZERO_PAGE},                         //0x86 zp
            {OpCode::SMB0, AddressMode::ZERO_PAGE},                         //0x87 zp
            {OpCode::DEY,  AddressMode::IMPLIED},                           //0x88 i
            {OpCode::BIT,  AddressMode::IMMEDIATE},                         //0x89 #
            {OpCode::TXA,  AddressMode::IMPLIED},                           //0x8A i
            {},                                                                                 //0x8B
            {OpCode::STY,  AddressMode::ABSOLUTE},                          //0x8C a
            {OpCode::STA,  AddressMode::ABSOLUTE},                          //0x8D a
            {OpCode::STX,  AddressMode::ABSOLUTE},                          //0x8E a
            {OpCode::BBS0, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x8F r
            /*0x9*/
            {OpCode::BCC,  AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x90 r
            {OpCode::STA,  AddressMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x91 (zp),y
            {OpCode::STA,  AddressMode::ZERO_PAGE_INDIRECT},                //0x92 (zp)
            {},                                                                                 //0x93
            {OpCode::STY,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x94 zp,x
            {OpCode::STA,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0x95 zp,x
            {OpCode::STX,  AddressMode::ZERO_PAGE_INDEXED_WITH_Y},          //0x96 zp,y
            {OpCode::SMB1, AddressMode::ZERO_PAGE},                         //0x97 zp
            {OpCode::TYA,  AddressMode::IMPLIED},                           //0x98 i
            {OpCode::STA,  AddressMode::ABSOLUTE_INDEXED_WITH_Y},           //0x99 a,y
            {OpCode::TXS,  AddressMode::IMPLIED},                           //0x9A i
            {},                                                                                 //0x9B
            {OpCode::STZ,  AddressMode::ABSOLUTE},                          //0x9C a
            {OpCode::STA,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x9D a,x
            {OpCode::STZ,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0x9E a,x
            {OpCode::BBS1, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0x9F r
            /*0xA*/
            {OpCode::LDY,  AddressMode::IMMEDIATE},                         //0xA0 #
            {OpCode::LDA,  AddressMode::ZERO_PAGE_INDEXED_INDIRECT},        //0xA1 (zp,x)
            {OpCode::LDX,  AddressMode::IMMEDIATE},                         //0xA2 #
            {},                                                                                 //0xA3
            {OpCode::LDY,  AddressMode::ZERO_PAGE},                         //0xA4 zp
            {OpCode::LDA,  AddressMode::ZERO_PAGE},                         //0xA5 zp
            {OpCode::LDX,  AddressMode::ZERO_PAGE},                         //0xA6 zp
            {OpCode::SMB2, AddressMode::ZERO_PAGE},                         //0xA7 zp
            {OpCode::TAY,  AddressMode::IMPLIED},                           //0xA8 i
            {OpCode::LDA,  AddressMode::IMMEDIATE},                         //0xA9 #
            {OpCode::TAX,  AddressMode::IMPLIED},                           //0xAA i
            {},                                                                                 //0xAB
            {OpCode::LDY,  AddressMode::ACCUMULATOR},                       //0xAC A
            {OpCode::LDA,  AddressMode::ABSOLUTE},                          //0xAD a
            {OpCode::LDX,  AddressMode::ABSOLUTE},                          //0xAE a
            {OpCode::BBS2, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0xAF r
            /*0xB*/
            {OpCode::BCS,  AddressMode::PROGRAM_COUNTER_RELATIVE},          //0xB0 r
            {OpCode::LDA,  AddressMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0xB1 (zp),y
            {OpCode::LDA,  AddressMode::ZERO_PAGE_INDIRECT},                //0xB2 (zp)
            {},                                                                                 //0xB3
            {OpCode::LDY,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0xB4 zp,x
            {OpCode::LDA,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0xB5 zp,x
            {OpCode::LDX,  AddressMode::ZERO_PAGE_INDEXED_WITH_Y},          //0xB6 zp,y
            {OpCode::SMB3, AddressMode::ZERO_PAGE},                         //0xB7 zp
            {OpCode::CLV,  AddressMode::IMPLIED},                           //0xB8 i
            {OpCode::LDA,  AddressMode::ABSOLUTE_INDEXED_WITH_Y},           //0xB9 A,y
            {OpCode::TSX,  AddressMode::IMPLIED},                           //0xBA i
            {},                                                                                 //0xBB
            {OpCode::LDY,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0xBC a,x
            {OpCode::LDA,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0xBD a,x
            {OpCode::LDX,  AddressMode::ABSOLUTE_INDEXED_WITH_Y},           //0xBE a,y
            {OpCode::BBS3, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0xBF r
            /*0xC*/
            {OpCode::CPY,  AddressMode::IMMEDIATE},                         //0xC0 #
            {OpCode::CMP,  AddressMode::ZERO_PAGE_INDEXED_INDIRECT},        //0xC1 (zp,x)
            {},                                                                                 //0xC2
            {},                                                                                 //0xC3
            {OpCode::CPY,  AddressMode::ZERO_PAGE},                         //0xC4 zp
            {OpCode::CMP,  AddressMode::ZERO_PAGE},                         //0xC5 zp
            {OpCode::DEC_, AddressMode::ZERO_PAGE},                         //0xC6 zp
            {OpCode::SMB4, AddressMode::ZERO_PAGE},                         //0xC7 zp
            {OpCode::INY,  AddressMode::IMPLIED},                           //0xC8 i
            {OpCode::CMP,  AddressMode::IMMEDIATE},                         //0xC9 #
            {OpCode::DEX,  AddressMode::IMPLIED},                           //0xCA i
            {OpCode::WAI,  AddressMode::IMPLIED},                           //0xCB i
            {OpCode::CPY,  AddressMode::ABSOLUTE},                          //0xCC a
            {OpCode::CMP,  AddressMode::ABSOLUTE},                          //0xCD a
            {OpCode::DEC_, AddressMode::ABSOLUTE},                          //0xCE a
            {OpCode::BBS4, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0xCF r
            /*0xD*/
            {OpCode::BNE,  AddressMode::PROGRAM_COUNTER_RELATIVE},          //0xD0 r
            {OpCode::CMP,  AddressMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0xD1 (zp),y
            {OpCode::CMP,  AddressMode::ZERO_PAGE_INDIRECT},                //0xD2 (zp)
            {},                                                                                 //0xD3
            {},                                                                                 //0xD4
            {OpCode::CMP,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0xD5 zp,x
            {OpCode::DEC_, AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0xD6 zp,x
            {OpCode::SMB5, AddressMode::ZERO_PAGE},                         //0xD7 zp
            {OpCode::CLD,  AddressMode::IMPLIED},                           //0xD8 i
            {OpCode::CMP,  AddressMode::ABSOLUTE_INDEXED_WITH_Y},           //0xD9 a,y
            {OpCode::PHX,  AddressMode::STACK},                             //0xDA s
            {OpCode::STP,  AddressMode::IMPLIED},                           //0xDB i
            {},                                                                                 //0xDC
            {OpCode::CMP,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0xDD a,x
            {OpCode::DEC_, AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0xDE a,x
            {OpCode::BBS5, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0xDF r
            /*0xE*/
            {OpCode::CPX,  AddressMode::IMMEDIATE},                         //0xE0 #
            {OpCode::SBC,  AddressMode::ZERO_PAGE_INDEXED_INDIRECT},        //0xE1 (zp,x)
            {},                                                                                 //0xE2
            {},                                                                                 //0xE3
            {OpCode::CPX,  AddressMode::ZERO_PAGE},                         //0xE4 zp
            {OpCode::SBC,  AddressMode::ZERO_PAGE},                         //0xE5 zp
            {OpCode::INC,  AddressMode::ZERO_PAGE},                         //0xE6 zp
            {OpCode::SMB6, AddressMode::ZERO_PAGE},                         //0xE7 zp
            {OpCode::INX,  AddressMode::IMPLIED},                           //0xE8 i
            {OpCode::SBC,  AddressMode::IMMEDIATE},                         //0xE9 #
            {OpCode::NOP,  AddressMode::IMPLIED},                           //0xEA i
            {},                                                                                 //0xEB
            {OpCode::CPX,  AddressMode::ABSOLUTE},                          //0xEC a
            {OpCode::SBC,  AddressMode::ABSOLUTE},                          //0xED a
            {OpCode::INC,  AddressMode::ABSOLUTE},                          //0xEE a
            {OpCode::BBS6, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0xEF r
            /*0xF*/
            {OpCode::BEQ,  AddressMode::PROGRAM_COUNTER_RELATIVE},          //0xF0 r
            {OpCode::SBC,  AddressMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0xF1 (zp),y
            {OpCode::SBC,  AddressMode::ZERO_PAGE_INDIRECT},                //0xF2 (zp)
            {},                                                                                 //0xF3
            {},                                                                                 //0xF4
            {OpCode::SBC,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0xF5 zp,x
            {OpCode::INC,  AddressMode::ZERO_PAGE_INDEXED_WITH_X},          //0xF6 zp,x
            {OpCode::SMB7, AddressMode::ZERO_PAGE},                         //0xF7 zp
            {OpCode::SED,  AddressMode::IMPLIED},                           //0xF8 i
            {OpCode::SBC,  AddressMode::ABSOLUTE_INDEXED_WITH_Y},           //0xF9 a,y
            {OpCode::PLX,  AddressMode::STACK},                             //0xFA s
            {},                                                                                 //0xFB
            {},                                                                                 //0xFC
            {OpCode::SBC,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0xFD a,x
            {OpCode::INC,  AddressMode::ABSOLUTE_INDEXED_WITH_X},           //0xFE a,x
            {OpCode::BBS7, AddressMode::PROGRAM_COUNTER_RELATIVE},          //0xFF r
    };

    String getAddressModeDescription(const AddressMode& addressMode);

    String getAddressModeSymbol(const AddressMode& addressMode);

    String getOpCodeName(const OpCode& opCode);
}

#endif