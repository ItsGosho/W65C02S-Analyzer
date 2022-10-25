#ifndef W65C02S_ANALYZER_OPCODES_H
#define W65C02S_ANALYZER_OPCODES_H

#include "Arduino.h"

namespace itsgosho {

    enum AddressingMode {
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

    enum Instruction {
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

    struct OpCode {
        Instruction instruction;
        AddressingMode addressingMode;
        bool hasOpCode;

        OpCode() : hasOpCode(false) {
        }

        OpCode(Instruction instruction, AddressingMode addressingMode)
                : instruction(instruction), addressingMode(addressingMode), hasOpCode(true) {
        }
    };


    /**
     * Each opcode has unique address.
     * For example 0xEA - NOP
     * https://www.westerndesigncenter.com/wdc/documentation/w65c02s.pdf : Page: 22
     * Some opcodes appear twice. That is because there is different addressing type for each of them. Page: 20
     * The array is used to visualize what opcode was read from the bus.
     */
    static OpCode opCodes[0xFF + 1] = {
            /*0x0*/
            {Instruction::BRK,  AddressingMode::STACK},                             //0x00 s
            {Instruction::ORA,  AddressingMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x01 (zp,x)
            {},                                                                                 //0x02
            {},                                                                                 //0x03
            {Instruction::TSB,  AddressingMode::ZERO_PAGE},                         //0x04 zp
            {Instruction::ORA,  AddressingMode::ZERO_PAGE},                         //0x05 zp
            {Instruction::ASL,  AddressingMode::ZERO_PAGE},                         //0x06 zp
            {Instruction::RMB0, AddressingMode::ZERO_PAGE},                         //0x07 zp
            {Instruction::PHP,  AddressingMode::STACK},                             //0x08 s
            {Instruction::ORA,  AddressingMode::IMMEDIATE},                         //0x09 #
            {Instruction::ASL,  AddressingMode::ACCUMULATOR},                       //0x0A A
            {},                                                                                 //0x0B
            {Instruction::TSB,  AddressingMode::ABSOLUTE},                          //0x0C a
            {Instruction::ORA,  AddressingMode::ABSOLUTE},                          //0x0D a
            {Instruction::ASL,  AddressingMode::ABSOLUTE},                          //0x0E a
            {Instruction::BBR0, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x0F r
            /*0x1*/
            {Instruction::BPL,  AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x10 r
            {Instruction::ORA,  AddressingMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x11 (zp),y
            {Instruction::ORA,  AddressingMode::ZERO_PAGE_INDIRECT},                //0x12 (zp)
            {},                                                                                 //0x13
            {Instruction::TRB,  AddressingMode::ZERO_PAGE},                         //0x14 zp
            {Instruction::ORA,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x15 zp,x
            {Instruction::ASL,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x16 zp,x
            {Instruction::RMB1, AddressingMode::ZERO_PAGE},                         //0x17 zp
            {Instruction::CLC,  AddressingMode::IMPLIED},                           //0x18 i
            {Instruction::ORA,  AddressingMode::ABSOLUTE_INDEXED_WITH_Y},           //0x19 a,y
            {Instruction::INC,  AddressingMode::ACCUMULATOR},                       //0x1A A
            {},                                                                                 //0x1B
            {Instruction::TRB,  AddressingMode::ABSOLUTE},                          //0x1C a
            {Instruction::ORA,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x1D a,x
            {Instruction::ASL,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x1E a,x
            {Instruction::BBR1, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x1F r
            /*0x2*/
            {Instruction::JSR,  AddressingMode::ABSOLUTE},                          //0x20 a
            {Instruction::AND,  AddressingMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x21 (zp),y
            {},                                                                                 //0x22
            {},                                                                                 //0x23
            {Instruction::BIT,  AddressingMode::ZERO_PAGE},                         //0x24 zp
            {Instruction::AND,  AddressingMode::ZERO_PAGE},                         //0x25 zp
            {Instruction::ROL,  AddressingMode::ZERO_PAGE},                         //0x26 zp
            {Instruction::RMB2, AddressingMode::ZERO_PAGE},                         //0x27 zp
            {Instruction::PLP,  AddressingMode::STACK},                             //0x28 s
            {Instruction::AND,  AddressingMode::IMMEDIATE},                         //0x29 #
            {Instruction::ROL,  AddressingMode::ACCUMULATOR},                       //0x2A A
            {},                                                                                 //0x2B
            {Instruction::BIT,  AddressingMode::ABSOLUTE},                          //0x2C a
            {Instruction::AND,  AddressingMode::ABSOLUTE},                          //0x2D a
            {Instruction::ROL,  AddressingMode::ABSOLUTE},                          //0x2E a
            {Instruction::BBR2, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x2F r
            /*0x3*/
            {Instruction::BMI,  AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x30 r
            {Instruction::AND,  AddressingMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x31 (zp),y
            {Instruction::AND,  AddressingMode::ZERO_PAGE_INDIRECT},                //0x32 (zp)
            {},                                                                                 //0x33
            {Instruction::BIT,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x34 zp,x
            {Instruction::AND,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x35 zp,x
            {Instruction::ROL,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x36 zp,x
            {Instruction::RMB3, AddressingMode::ZERO_PAGE},                         //0x37 zp
            {Instruction::SEC,  AddressingMode::IMPLIED},                           //0x38 I
            {Instruction::AND,  AddressingMode::ABSOLUTE_INDEXED_WITH_Y},           //0x39 a,y
            {Instruction::DEC_, AddressingMode::ACCUMULATOR},                       //0x3A A*
            {},                                                                                 //0x3B
            {Instruction::BIT,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x3C a,x
            {Instruction::AND,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x3D a,x
            {Instruction::ROL,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x3E a,x
            {Instruction::BBR2, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x3F r
            /*0x4*/
            {Instruction::RTI,  AddressingMode::STACK},                             //0x40 s
            {Instruction::EOR,  AddressingMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x41 (zp,x)
            {},                                                                                 //0x42
            {},                                                                                 //0x43
            {},                                                                                 //0x44
            {Instruction::EOR,  AddressingMode::ZERO_PAGE},                         //0x45 zp
            {Instruction::LSR,  AddressingMode::ZERO_PAGE},                         //0x46 zp
            {Instruction::RMB4, AddressingMode::ZERO_PAGE},                         //0x47 zp
            {Instruction::PHA,  AddressingMode::STACK},                             //0x48 s
            {Instruction::EOR,  AddressingMode::IMMEDIATE},                         //0x49 #
            {Instruction::LSR,  AddressingMode::ACCUMULATOR},                       //0x4A A
            {},                                                                                 //0x4B
            {Instruction::JMP,  AddressingMode::ABSOLUTE},                          //0x4C a
            {Instruction::EOR,  AddressingMode::ABSOLUTE},                          //0x4D a
            {Instruction::LSR,  AddressingMode::ABSOLUTE},                          //0x4E a
            {Instruction::BBR4, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x4F r
            /*0x5*/
            {Instruction::BVC,  AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x50 r
            {Instruction::EOR,  AddressingMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x51 (zp),y
            {Instruction::EOR,  AddressingMode::ZERO_PAGE},                         //0x52 (zp)
            {},                                                                                 //0x53
            {},                                                                                 //0x54
            {Instruction::EOR,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x55 zp,x
            {Instruction::LSR,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x56 zp,x
            {Instruction::RMB5, AddressingMode::ZERO_PAGE},                         //0x57 zp
            {Instruction::CLI,  AddressingMode::IMPLIED},                           //0x58 i
            {Instruction::EOR,  AddressingMode::ABSOLUTE_INDEXED_WITH_Y},           //0x59 a,y
            {Instruction::PHY,  AddressingMode::STACK},                             //0x5A s
            {},                                                                                 //0x5B
            {},                                                                                 //0x5C
            {Instruction::EOR,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x5D a,x
            {Instruction::LSR,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x5E a,x
            {Instruction::BBR5, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x5F r
            /*0x6*/
            {Instruction::RTS,  AddressingMode::STACK},                             //0x60 s
            {Instruction::ADC_, AddressingMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x61 (zp,x)
            {},                                                                                 //0x62
            {},                                                                                 //0x63
            {Instruction::STZ,  AddressingMode::ZERO_PAGE},                         //0x64 zp
            {Instruction::ADC_, AddressingMode::ZERO_PAGE},                         //0x65 zp
            {Instruction::ROR,  AddressingMode::ZERO_PAGE},                         //0x66 zp
            {Instruction::RMB6, AddressingMode::ZERO_PAGE},                         //0x67 zp
            {Instruction::PLA,  AddressingMode::STACK},                             //0x68 s
            {Instruction::ADC_, AddressingMode::IMMEDIATE},                         //0x69 #
            {Instruction::ROR,  AddressingMode::ACCUMULATOR},                       //0x6A A
            {},                                                                                 //0x6B
            {Instruction::JMP,  AddressingMode::ABSOLUTE_INDIRECT},                 //0x6C (a)
            {Instruction::ADC_, AddressingMode::ABSOLUTE},                          //0x6D a
            {Instruction::ROR,  AddressingMode::ABSOLUTE},                          //0x6E a
            {Instruction::BBR6, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x6F r
            /*0x7*/
            {Instruction::BVS,  AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x70 r
            {Instruction::ADC_, AddressingMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x71 (zp),y
            {Instruction::ADC_, AddressingMode::ZERO_PAGE_INDIRECT},                //0x72 (zp)
            {},                                                                                 //0x73
            {Instruction::STZ,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x74 zp,x
            {Instruction::ADC_, AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x75 zp,x
            {Instruction::ROR,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x76 zp,x
            {Instruction::RMB7, AddressingMode::ZERO_PAGE},                         //0x77 zp
            {Instruction::SEI,  AddressingMode::IMPLIED},                           //0x78 i
            {Instruction::ADC_, AddressingMode::ABSOLUTE_INDEXED_WITH_Y},           //0x79 a,y
            {Instruction::PLY,  AddressingMode::STACK},                             //0x7A s
            {},                                                                                 //0x7B
            {Instruction::JMP,  AddressingMode::ABSOLUTE_INDEXED_INDIRECT},         //0x7C (a,x)
            {Instruction::ADC_, AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x7D a,x
            {Instruction::ROR,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x7E a,x
            {Instruction::BBR7, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x7F r
            /*0x8*/
            {Instruction::BRA,  AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x80 r
            {Instruction::STA,  AddressingMode::ZERO_PAGE_INDEXED_INDIRECT},        //0x81 (zp,x)
            {},                                                                                 //0x82
            {},                                                                                 //0x83
            {Instruction::STY,  AddressingMode::ZERO_PAGE},                         //0x84 zp
            {Instruction::STA,  AddressingMode::ZERO_PAGE},                         //0x85 zp
            {Instruction::STX,  AddressingMode::ZERO_PAGE},                         //0x86 zp
            {Instruction::SMB0, AddressingMode::ZERO_PAGE},                         //0x87 zp
            {Instruction::DEY,  AddressingMode::IMPLIED},                           //0x88 i
            {Instruction::BIT,  AddressingMode::IMMEDIATE},                         //0x89 #
            {Instruction::TXA,  AddressingMode::IMPLIED},                           //0x8A i
            {},                                                                                 //0x8B
            {Instruction::STY,  AddressingMode::ABSOLUTE},                          //0x8C a
            {Instruction::STA,  AddressingMode::ABSOLUTE},                          //0x8D a
            {Instruction::STX,  AddressingMode::ABSOLUTE},                          //0x8E a
            {Instruction::BBS0, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x8F r
            /*0x9*/
            {Instruction::BCC,  AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x90 r
            {Instruction::STA,  AddressingMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0x91 (zp),y
            {Instruction::STA,  AddressingMode::ZERO_PAGE_INDIRECT},                //0x92 (zp)
            {},                                                                                 //0x93
            {Instruction::STY,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x94 zp,x
            {Instruction::STA,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0x95 zp,x
            {Instruction::STX,  AddressingMode::ZERO_PAGE_INDEXED_WITH_Y},          //0x96 zp,y
            {Instruction::SMB1, AddressingMode::ZERO_PAGE},                         //0x97 zp
            {Instruction::TYA,  AddressingMode::IMPLIED},                           //0x98 i
            {Instruction::STA,  AddressingMode::ABSOLUTE_INDEXED_WITH_Y},           //0x99 a,y
            {Instruction::TXS,  AddressingMode::IMPLIED},                           //0x9A i
            {},                                                                                 //0x9B
            {Instruction::STZ,  AddressingMode::ABSOLUTE},                          //0x9C a
            {Instruction::STA,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x9D a,x
            {Instruction::STZ,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0x9E a,x
            {Instruction::BBS1, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0x9F r
            /*0xA*/
            {Instruction::LDY,  AddressingMode::IMMEDIATE},                         //0xA0 #
            {Instruction::LDA,  AddressingMode::ZERO_PAGE_INDEXED_INDIRECT},        //0xA1 (zp,x)
            {Instruction::LDX,  AddressingMode::IMMEDIATE},                         //0xA2 #
            {},                                                                                 //0xA3
            {Instruction::LDY,  AddressingMode::ZERO_PAGE},                         //0xA4 zp
            {Instruction::LDA,  AddressingMode::ZERO_PAGE},                         //0xA5 zp
            {Instruction::LDX,  AddressingMode::ZERO_PAGE},                         //0xA6 zp
            {Instruction::SMB2, AddressingMode::ZERO_PAGE},                         //0xA7 zp
            {Instruction::TAY,  AddressingMode::IMPLIED},                           //0xA8 i
            {Instruction::LDA,  AddressingMode::IMMEDIATE},                         //0xA9 #
            {Instruction::TAX,  AddressingMode::IMPLIED},                           //0xAA i
            {},                                                                                 //0xAB
            {Instruction::LDY,  AddressingMode::ACCUMULATOR},                       //0xAC A
            {Instruction::LDA,  AddressingMode::ABSOLUTE},                          //0xAD a
            {Instruction::LDX,  AddressingMode::ABSOLUTE},                          //0xAE a
            {Instruction::BBS2, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0xAF r
            /*0xB*/
            {Instruction::BCS,  AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0xB0 r
            {Instruction::LDA,  AddressingMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0xB1 (zp),y
            {Instruction::LDA,  AddressingMode::ZERO_PAGE_INDIRECT},                //0xB2 (zp)
            {},                                                                                 //0xB3
            {Instruction::LDY,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0xB4 zp,x
            {Instruction::LDA,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0xB5 zp,x
            {Instruction::LDX,  AddressingMode::ZERO_PAGE_INDEXED_WITH_Y},          //0xB6 zp,y
            {Instruction::SMB3, AddressingMode::ZERO_PAGE},                         //0xB7 zp
            {Instruction::CLV,  AddressingMode::IMPLIED},                           //0xB8 i
            {Instruction::LDA,  AddressingMode::ABSOLUTE_INDEXED_WITH_Y},           //0xB9 A,y
            {Instruction::TSX,  AddressingMode::IMPLIED},                           //0xBA i
            {},                                                                                 //0xBB
            {Instruction::LDY,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0xBC a,x
            {Instruction::LDA,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0xBD a,x
            {Instruction::LDX,  AddressingMode::ABSOLUTE_INDEXED_WITH_Y},           //0xBE a,y
            {Instruction::BBS3, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0xBF r
            /*0xC*/
            {Instruction::CPY,  AddressingMode::IMMEDIATE},                         //0xC0 #
            {Instruction::CMP,  AddressingMode::ZERO_PAGE_INDEXED_INDIRECT},        //0xC1 (zp,x)
            {},                                                                                 //0xC2
            {},                                                                                 //0xC3
            {Instruction::CPY,  AddressingMode::ZERO_PAGE},                         //0xC4 zp
            {Instruction::CMP,  AddressingMode::ZERO_PAGE},                         //0xC5 zp
            {Instruction::DEC_, AddressingMode::ZERO_PAGE},                         //0xC6 zp
            {Instruction::SMB4, AddressingMode::ZERO_PAGE},                         //0xC7 zp
            {Instruction::INY,  AddressingMode::IMPLIED},                           //0xC8 i
            {Instruction::CMP,  AddressingMode::IMMEDIATE},                         //0xC9 #
            {Instruction::DEX,  AddressingMode::IMPLIED},                           //0xCA i
            {Instruction::WAI,  AddressingMode::IMPLIED},                           //0xCB i
            {Instruction::CPY,  AddressingMode::ABSOLUTE},                          //0xCC a
            {Instruction::CMP,  AddressingMode::ABSOLUTE},                          //0xCD a
            {Instruction::DEC_, AddressingMode::ABSOLUTE},                          //0xCE a
            {Instruction::BBS4, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0xCF r
            /*0xD*/
            {Instruction::BNE,  AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0xD0 r
            {Instruction::CMP,  AddressingMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0xD1 (zp),y
            {Instruction::CMP,  AddressingMode::ZERO_PAGE_INDIRECT},                //0xD2 (zp)
            {},                                                                                 //0xD3
            {},                                                                                 //0xD4
            {Instruction::CMP,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0xD5 zp,x
            {Instruction::DEC_, AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0xD6 zp,x
            {Instruction::SMB5, AddressingMode::ZERO_PAGE},                         //0xD7 zp
            {Instruction::CLD,  AddressingMode::IMPLIED},                           //0xD8 i
            {Instruction::CMP,  AddressingMode::ABSOLUTE_INDEXED_WITH_Y},           //0xD9 a,y
            {Instruction::PHX,  AddressingMode::STACK},                             //0xDA s
            {Instruction::STP,  AddressingMode::IMPLIED},                           //0xDB i
            {},                                                                                 //0xDC
            {Instruction::CMP,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0xDD a,x
            {Instruction::DEC_, AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0xDE a,x
            {Instruction::BBS5, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0xDF r
            /*0xE*/
            {Instruction::CPX,  AddressingMode::IMMEDIATE},                         //0xE0 #
            {Instruction::SBC,  AddressingMode::ZERO_PAGE_INDEXED_INDIRECT},        //0xE1 (zp,x)
            {},                                                                                 //0xE2
            {},                                                                                 //0xE3
            {Instruction::CPX,  AddressingMode::ZERO_PAGE},                         //0xE4 zp
            {Instruction::SBC,  AddressingMode::ZERO_PAGE},                         //0xE5 zp
            {Instruction::INC,  AddressingMode::ZERO_PAGE},                         //0xE6 zp
            {Instruction::SMB6, AddressingMode::ZERO_PAGE},                         //0xE7 zp
            {Instruction::INX,  AddressingMode::IMPLIED},                           //0xE8 i
            {Instruction::SBC,  AddressingMode::IMMEDIATE},                         //0xE9 #
            {Instruction::NOP,  AddressingMode::IMPLIED},                           //0xEA i
            {},                                                                                 //0xEB
            {Instruction::CPX,  AddressingMode::ABSOLUTE},                          //0xEC a
            {Instruction::SBC,  AddressingMode::ABSOLUTE},                          //0xED a
            {Instruction::INC,  AddressingMode::ABSOLUTE},                          //0xEE a
            {Instruction::BBS6, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0xEF r
            /*0xF*/
            {Instruction::BEQ,  AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0xF0 r
            {Instruction::SBC,  AddressingMode::ZERO_PAGE_INDIRECT_INDEXED_WITH_Y}, //0xF1 (zp),y
            {Instruction::SBC,  AddressingMode::ZERO_PAGE_INDIRECT},                //0xF2 (zp)
            {},                                                                                 //0xF3
            {},                                                                                 //0xF4
            {Instruction::SBC,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0xF5 zp,x
            {Instruction::INC,  AddressingMode::ZERO_PAGE_INDEXED_WITH_X},          //0xF6 zp,x
            {Instruction::SMB7, AddressingMode::ZERO_PAGE},                         //0xF7 zp
            {Instruction::SED,  AddressingMode::IMPLIED},                           //0xF8 i
            {Instruction::SBC,  AddressingMode::ABSOLUTE_INDEXED_WITH_Y},           //0xF9 a,y
            {Instruction::PLX,  AddressingMode::STACK},                             //0xFA s
            {},                                                                                 //0xFB
            {},                                                                                 //0xFC
            {Instruction::SBC,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0xFD a,x
            {Instruction::INC,  AddressingMode::ABSOLUTE_INDEXED_WITH_X},           //0xFE a,x
            {Instruction::BBS7, AddressingMode::PROGRAM_COUNTER_RELATIVE},          //0xFF r
    };

    String getAddressingModeDescription(const AddressingMode& addressingMode);

    String getAddressingModeSymbol(const AddressingMode& addressingMode);

    String getInstructionName(const Instruction& instruction);
}

#endif