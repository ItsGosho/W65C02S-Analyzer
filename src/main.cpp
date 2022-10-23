#include <Arduino.h>
#include "utils.h"

using namespace itsgosho;

#define MP_RWB_PIN 2
#define MP_CLOCK_PIN 3

#define MP_A0_PIN 22
#define MP_A1_PIN 24
#define MP_A2_PIN 26
#define MP_A3_PIN 28
#define MP_A4_PIN 30
#define MP_A5_PIN 32
#define MP_A6_PIN 34
#define MP_A7_PIN 36
#define MP_A8_PIN 38
#define MP_A9_PIN 40
#define MP_A10_PIN 42
#define MP_A11_PIN 44
#define MP_A12_PIN 46
#define MP_A13_PIN 48
#define MP_A14_PIN 50
#define MP_A15_PIN 52

#define MP_D0_PIN 31
#define MP_D1_PIN 33
#define MP_D2_PIN 35
#define MP_D3_PIN 37
#define MP_D4_PIN 39
#define MP_D5_PIN 41
#define MP_D6_PIN 43
#define MP_D7_PIN 45

#define MP_RST_SEQ_ADDR 0xffff /*Received address indicating a reset sequence*/
#define MP_RST_LB_ADDR 0xfffc /*Received address indicating low byte  set*/
#define MP_RST_HB_ADDR 0xfffd /*Received address indicating high byte set*/
#define MP_RST_INST_COUNT 7 /*Total number of reset instructions*/

#define ADDR_VISUAL_MODE HEX /*Visualize the address in binary or hexadecimal*/
#define DATA_VISUAL_MODE HEX /*Visualize the data in binary or hexadecimal*/

int mpAddressPins[16] = {MP_A0_PIN, MP_A1_PIN, MP_A2_PIN, MP_A3_PIN, MP_A4_PIN, MP_A5_PIN, MP_A6_PIN, MP_A7_PIN, MP_A8_PIN, MP_A9_PIN, MP_A10_PIN, MP_A11_PIN, MP_A12_PIN, MP_A13_PIN, MP_A14_PIN, MP_A15_PIN};
int mpDataPins[8] = {MP_D0_PIN, MP_D1_PIN, MP_D2_PIN, MP_D3_PIN, MP_D4_PIN, MP_D5_PIN, MP_D6_PIN, MP_D7_PIN};

enum AddressMode {
    ABSOLUTE = 0,                          //a
    ABSOLUTE_INDEXED_INDIRECT = 1,         // (a,x)
    ABSOLUTE_INDEXED_WITH_X = 2,           //a,x
    ABSOLUTE_INDEXED_WITH_Y = 3,           //a,y
    ABSOLUTE_INDIRECT_A = 4,               //(a)
    ACCUMULATOR = 5,                       //A
    IMMEDIATE = 6,                         //#
    IMPLIED = 7,                           //i
    PROGRAM_COUNTER_RELATIVE = 8,          //r
    STACK = 9,                             //s
    ZERO_PAGE = 10,                        //zp
    ZERO_PAGE_INDEXED_INDIRECT = 11,       //zp,x
    ZERO_PAGE_INDEXED_WITH_X = 12,         // zp,x
    ZERO_PAGE_INDEXED_WITH_Y = 13,         // zp,y
    ZERO_PAGE_INDIRECT = 14,               // (zp)
    ZERO_PAGE_INDIRECT_INDEXED_WITH_Y = 15 // (zp),y
};

enum OpCodeType {
    JSR = 0,
    LDA = 1,
    LDX = 2,
    LDY = 3,
    LSR = 4,
    NOP = 5,
    ORA = 6,
    PHA = 7,
    PHP = 8,
    PHX = 9,
    PHY = 10,
    PLA = 11,
    PLP = 12,
    PLX = 13,
    PLY = 14,
    RMB0 = 15,
    RMB1 = 16,
    RMB2 = 17,
    RMB3 = 18,
    RMB4 = 19,
    RMB5 = 20,
    RMB6 = 21,
    RMB7 = 22,
    ROL = 23,
    ROR = 24,
    RTI = 25,
    RTS = 26,
    SBC = 27,
    SEC = 28,
    SED = 29,
    SEI = 30,
    SMB0 = 31,
    SMB1 = 32,
    SMB2 = 33,
    SMB3 = 34,
    SMB4 = 35,
    SMB5 = 36,
    SMB6 = 37,
    SMB7 = 38,
    STA = 39,
    STP = 40,
    STX = 41,
    STY = 42,
    STZ = 43,
    TAX = 44,
    TAY = 45,
    TRB = 46,
    TSB = 47,
    TSX = 48,
    TXA = 49,
    TXS = 50,
    TYA = 51,
    WAI = 52
};

struct OpCode {
    OpCodeType type;
    AddressMode addressMode;
};


/**
 * Each opcode has unique address.
 * For example 0xEA - NOP
 * https://www.westerndesigncenter.com/wdc/documentation/w65c02s.pdf : Page: 22
 * Some opcodes appear twice. That is because there is different addressing type for each of them. Page: 20
 * The array is used to visualize what opcode was read from the bus.
 */
static String opCodeNames[0xFF + 1] = {
        /*0*/ "BRK", "ORA", "", "", "TSB", "ORA", "ASL", "RMB0", "PHP", "ORA", "ASL", "", "TSB", "ORA", "ASL", "BBR0",
        /*1*/ "BPL", "ORA", "ORA", "", "TRB", "ORA", "ASL", "RMB1", "CLC", "ORA", "INC", "", "TRB", "ORA", "ASL", "BBR1",
        /*2*/ "JSR", "AND", "", "", "BIT", "AND", "ROL", "RMB2", "PLP", "AND", "ROL", "", "BIT", "AND", "ROL", "BBR2",
        /*3*/ "BMI", "AND", "AND", "", "BIT", "AND", "ROL", "RMB3", "SEC", "AND", "DEC", "", "BIT", "AND", "ROL", "BBR3",
        /*4*/ "RTI", "EOR", "", "", "", "EOR", "LSR", "RMB4", "PHA", "EOR", "LSR", "", "JMP", "EOR", "LSR", "BBR4",
        /*5*/ "BVC", "EOR", "EOR", "", "", "EOR", "LSR", "RMB5", "CLI", "EOR", "PHY", "", "", "EOR", "LSR", "BBR5",
        /*6*/ "RTS", "ADC", "", "", "STZ", "ADC", "ROR", "RMB6", "PLA", "ADC", "ROR", "", "JMP", "ADC", "ROR", "BBR6",
        /*7*/ "BVS", "ADC", "ADC", "", "STZ", "ADC", "ROR", "RMB7", "SEI", "ADC", "PLY", "", "JMP", "ADC", "ROR", "BBR7",
        /*8*/ "BRA", "STA", "", "", "STY", "STA", "STX", "SMB0", "DEY", "BIT", "TXA", "", "STY", "STA", "STX", "BBS0",
        /*9*/ "BCC", "STA", "STA", "", "STY", "STA", "STX", "SMB1", "TYA", "STA", "TXS", "", "STZ", "STA", "STZ", "BBS1",
        /*A*/ "LDY", "LDA", "LDX", "", "LDY", "LDA", "LDX", "SMB2", "TAY", "LDA", "TAX", "", "LDY", "LDA", "LDX", "BBS2",
        /*B*/ "BCS", "LDA", "LDA", "", "LDY", "LDA", "LDX", "SMB3", "CLV", "LDA", "TSX", "", "LDY", "LDA", "LDX", "BBS3",
        /*C*/ "CPY", "CMP", "", "", "CPY", "CMP", "DEC", "SMB4", "INY", "CMP", "DEX", "WAI", "CPY", "CMP", "DEC", "BBS4",
        /*D*/ "BNE", "CMP", "CMP", "", "", "CMP", "DEC", "SMB5", "CLD", "CMP", "PHX", "STP", "", "CMP", "DEC", "BBS5",
        /*E*/ "CPX", "SBC", "", "", "CPX", "SBC", "INC", "SMB6", "INX", "SBC", "NOP", "", "CPX", "SBC", "INC", "BBS6",
        /*F*/ "BEQ", "SBC", "SBC", "", "", "SBC", "INC", "SMB7", "SED", "SBC", "PLX", "", "", "SBC", "INC", "BBS7"};

volatile uint16_t instructionCounter = 1;
volatile bool isResetSequence = false;

void onClockRisingEdge() {
    char output[100];

    bool operation = digitalRead(MP_RWB_PIN);
    unsigned int address = digitalRead(mpAddressPins, LSBFIRST);
    unsigned int data = digitalRead(mpDataPins, LSBFIRST);

    if (address == MP_RST_SEQ_ADDR) {
        instructionCounter = 1;
        isResetSequence = true;
    }

    if (instructionCounter > MP_RST_INST_COUNT)
        isResetSequence = false;

    String opCodeName = "[OpCode: " + opCodeNames[data] + "]";
    sprintf(output,
            "%03u. [%c] (Address: %04x ; %05u - Data: %02x ; %03u) %s %s %s",
            instructionCounter,
            (operation ? 'R' : 'W'),
            address,
            address,
            data,
            data,
            !isResetSequence && opCodeName != "" ? opCodeName.begin() : "",
            isResetSequence ? "[Resetting]" : "",
            address == MP_RST_LB_ADDR ? "[Program Counter: Low Byte]" : (address == MP_RST_HB_ADDR ? "[Program Counter: High Byte]" : ""));
    Serial.println(output);

    instructionCounter++;
}

void setup() {
    Serial.begin(9600);
    Serial.println("The address and data are displayed in hexadecimal ; decimal format!");

    pinMode(MP_RWB_PIN, INPUT);
    pinMode(MP_CLOCK_PIN, INPUT);
    pinModes(mpAddressPins, INPUT);
    pinModes(mpDataPins, INPUT);

    attachInterrupt(digitalPinToInterrupt(MP_CLOCK_PIN), onClockRisingEdge, RISING);
}

void loop() {
// write your code here
}