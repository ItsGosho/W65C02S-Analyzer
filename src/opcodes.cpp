#include "opcodes.h"

String itsgosho::getAddressingModeDescription(const AddressingMode& addressingMode) {

    switch (addressingMode) {
        case ABSOLUTE:
            return "Absolute";
        case ABSOLUTE_INDEXED_INDIRECT:
            return "Absolute Indexed Indirect";
        case ABSOLUTE_INDEXED_WITH_X:
            return "Absolute Indexed with X";
        case ABSOLUTE_INDEXED_WITH_Y:
            return "Absolute Indexed with Y";
        case ABSOLUTE_INDIRECT:
            return "Absolute Indirect";
        case ACCUMULATOR:
            return "Accumulator";
        case IMMEDIATE:
            return "Immediate";
        case IMPLIED:
            return "Implied";
        case PROGRAM_COUNTER_RELATIVE:
            return "Program Counter Relative";
        case STACK:
            return "Stack";
        case ZERO_PAGE:
            return "Zero Page";
        case ZERO_PAGE_INDEXED_INDIRECT:
            return "Zero Page Indexed Indirect";
        case ZERO_PAGE_INDEXED_WITH_X:
            return "Zero Page Indexed with X";
        case ZERO_PAGE_INDEXED_WITH_Y:
            return "Zero Page Indexed with Y";
        case ZERO_PAGE_INDIRECT:
            return "Zero Page Indirect";
        case ZERO_PAGE_INDIRECT_INDEXED_WITH_Y:
            return "Zero Page Indirect Indexed with Y";
    }

    return "Address Mode Name not implemented!";
}

String itsgosho::getAddressingModeSymbol(const AddressingMode& addressingMode) {
    switch (addressingMode) {
        case ABSOLUTE:
            return "a";
        case ABSOLUTE_INDEXED_INDIRECT:
            return "(a,x)";
        case ABSOLUTE_INDEXED_WITH_X:
            return "a,x";
        case ABSOLUTE_INDEXED_WITH_Y:
            return "a,y";
        case ABSOLUTE_INDIRECT:
            return "(a)";
        case ACCUMULATOR:
            return "A";
        case IMMEDIATE:
            return "#";
        case IMPLIED:
            return "i";
        case PROGRAM_COUNTER_RELATIVE:
            return "r";
        case STACK:
            return "s";
        case ZERO_PAGE:
            return "zp";
        case ZERO_PAGE_INDEXED_INDIRECT:
            return "(zp,x)";
        case ZERO_PAGE_INDEXED_WITH_X:
            return "zp,x";
        case ZERO_PAGE_INDEXED_WITH_Y:
            return "zp,y";
        case ZERO_PAGE_INDIRECT:
            return "(zp)";
        case ZERO_PAGE_INDIRECT_INDEXED_WITH_Y:
            return "(zp),y";
    }

    return "Addressing Mode Symbol not implemented!";
}

String itsgosho::getInstructionName(const Instruction& instruction) {

    switch (instruction) {
        case ADC_:
            return "ADC_";
        case AND:
            return "AND";
        case ASL:
            return "ASL";
        case BBR0:
            return "BBR0";
        case BBR1:
            return "BBR1";
        case BBR2:
            return "BBR2";
        case BBR3:
            return "BBR3";
        case BBR4:
            return "BBR4";
        case BBR5:
            return "BBR5";
        case BBR6:
            return "BBR6";
        case BBR7:
            return "BBR7";
        case BBS0:
            return "BBS0";
        case BBS1:
            return "BBS1";
        case BBS2:
            return "BBS2";
        case BBS3:
            return "BBS3";
        case BBS4:
            return "BBS4";
        case BBS5:
            return "BBS5";
        case BBS6:
            return "BBS6";
        case BBS7:
            return "BBS7";
        case BCC:
            return "BCC";
        case BCS:
            return "BCS";
        case BEQ:
            return "BEQ";
        case BIT:
            return "BIT";
        case BMI:
            return "BMI";
        case BNE:
            return "BNE";
        case BPL:
            return "BPL";
        case BRA:
            return "BRA";
        case BRK:
            return "BRK";
        case BVC:
            return "BVC";
        case BVS:
            return "BVS";
        case CLC:
            return "CLC";
        case CLD:
            return "CLD";
        case CLI:
            return "CLI";
        case CLV:
            return "CLV";
        case CMP:
            return "CMP";
        case CPX:
            return "CPX";
        case CPY:
            return "CPY";
        case DEC_:
            return "DEC_";
        case DEX:
            return "DEX";
        case DEY:
            return "DEY";
        case EOR:
            return "EOR";
        case INC:
            return "INC";
        case INX:
            return "INX";
        case INY:
            return "INY";
        case JMP:
            return "JMP";
        case JSR:
            return "JSR";
        case LDA:
            return "LDA";
        case LDX:
            return "LDX";
        case LDY:
            return "LDY";
        case LSR:
            return "LSR";
        case NOP:
            return "NOP";
        case ORA:
            return "ORA";
        case PHA:
            return "PHA";
        case PHP:
            return "PHP";
        case PHX:
            return "PHX";
        case PHY:
            return "PHY";
        case PLA:
            return "PLA";
        case PLP:
            return "PLP";
        case PLX:
            return "PLX";
        case PLY:
            return "PLY";
        case RMB0:
            return "RMB0";
        case RMB1:
            return "RMB1";
        case RMB2:
            return "RMB2";
        case RMB3:
            return "RMB3";
        case RMB4:
            return "RMB4";
        case RMB5:
            return "RMB5";
        case RMB6:
            return "RMB6";
        case RMB7:
            return "RMB7";
        case ROL:
            return "ROL";
        case ROR:
            return "ROR";
        case RTI:
            return "RTI";
        case RTS:
            return "RTS";
        case SBC:
            return "SBC";
        case SEC:
            return "SEC";
        case SED:
            return "SED";
        case SEI:
            return "SEI";
        case SMB0:
            return "SMB0";
        case SMB1:
            return "SMB1";
        case SMB2:
            return "SMB2";
        case SMB3:
            return "SMB3";
        case SMB4:
            return "SMB4";
        case SMB5:
            return "SMB5";
        case SMB6:
            return "SMB6";
        case SMB7:
            return "SMB7";
        case STA:
            return "STA";
        case STP:
            return "STP";
        case STX:
            return "STX";
        case STY:
            return "STY";
        case STZ:
            return "STZ";
        case TAX:
            return "TAX";
        case TAY:
            return "TAY";
        case TRB:
            return "TRB";
        case TSB:
            return "TSB";
        case TSX:
            return "TSX";
        case TXA:
            return "TXA";
        case TXS:
            return "TXS";
        case TYA:
            return "TYA";
        case WAI:
            return "WAI";
    }
    return "Instruction name not implemented!";
}

int itsgosho::getOpCodeClockCycles(const itsgosho::OpCode& opCode) {
    return getAddressingModeClockCycles(opCode.addressingMode);
}

int itsgosho::getAddressingModeClockCycles(const itsgosho::AddressingMode& addressingMode) {

    switch (addressingMode) {
        case ABSOLUTE:
            return 3;
        case ABSOLUTE_INDEXED_INDIRECT:
            return 0;
        case ABSOLUTE_INDEXED_WITH_X:
            return 0;
        case ABSOLUTE_INDEXED_WITH_Y:
            return 0;
        case ABSOLUTE_INDIRECT:
            return 0;
        case ACCUMULATOR:
            return 0;
        case IMMEDIATE:
            return 2;
        case IMPLIED:
            return 2;
        case PROGRAM_COUNTER_RELATIVE:
            return 0;
        case STACK:
            return 0;
        case ZERO_PAGE:
            return 0;
        case ZERO_PAGE_INDEXED_INDIRECT:
            return 0;
        case ZERO_PAGE_INDEXED_WITH_X:
            return 0;
        case ZERO_PAGE_INDEXED_WITH_Y:
            return 0;
        case ZERO_PAGE_INDIRECT:
            return 0;
        case ZERO_PAGE_INDIRECT_INDEXED_WITH_Y:
            return 0;
    }

    return 0;
}
