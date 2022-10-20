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

int mpAddressPins[16] = {MP_A0_PIN, MP_A1_PIN, MP_A2_PIN, MP_A3_PIN, MP_A4_PIN, MP_A5_PIN, MP_A6_PIN, MP_A7_PIN, MP_A8_PIN, MP_A9_PIN, MP_A10_PIN, MP_A11_PIN, MP_A12_PIN, MP_A13_PIN, MP_A14_PIN, MP_A15_PIN};
int mpDataPins[8] = {MP_D0_PIN, MP_D1_PIN, MP_D2_PIN, MP_D3_PIN, MP_D4_PIN, MP_D5_PIN, MP_D6_PIN, MP_D7_PIN};

/**
 * Each opcode has unique address.
 * For example 0xEA - NOP
 * https://www.westerndesigncenter.com/wdc/documentation/w65c02s.pdf : Page: 22
 * Some opcodes appear twice. That is because there is different addressing type for each of them. Page: 20
 * The array is used to visualize what opcode was read from the bus.
 */
static char* opCodeNames[0xFF + 1] = {
        /*0*/ "BRK", "ORA", nullptr, nullptr, "TSB", "ORA", "ASL", "RMB0", "PHP", "ORA", "ASL", nullptr, "TSB", "ORA", "ASL", "BBR0",
        /*1*/ "BPL", "ORA", "ORA", nullptr, "TRB", "ORA", "ASL", "RMB1", "CLC", "ORA", "INC", nullptr, "TRB", "ORA", "ASL", "BBR1",
        /*2*/ "JSR", "AND", nullptr, nullptr, "BIT", "AND", "ROL", "RMB2", "PLP", "AND", "ROL", nullptr, "BIT", "AND", "ROL", "BBR2",
        /*3*/ "BMI", "AND", "AND", nullptr, "BIT", "AND", "ROL", "RMB3", "SEC", "AND", "DEC", nullptr, "BIT", "AND", "ROL", "BBR3",
        /*4*/ "RTI", "EOR", nullptr, nullptr, nullptr, "EOR", "LSR", "RMB4", "PHA", "EOR", "LSR", nullptr, "JMP", "EOR", "LSR", "BBR4",
        /*5*/ "BVC", "EOR", "EOR", nullptr, nullptr, "EOR", "LSR", "RMB5", "CLI", "EOR", "PHY", nullptr, nullptr, "EOR", "LSR", "BBR5",
        /*6*/ "RTS", "ADC", nullptr, nullptr, "STZ", "ADC", "ROR", "RMB6", "PLA", "ADC", "ROR", nullptr, "JMP", "ADC", "ROR", "BBR6",
        /*7*/ "BVS", "ADC", "ADC", nullptr, "STZ", "ADC", "ROR", "RMB7", "SEI", "ADC", "PLY", nullptr, "JMP", "ADC", "ROR", "BBR7",
        /*8*/ "BRA", "STA", nullptr, nullptr, "STY", "STA", "STX", "SMB0", "DEY", "BIT", "TXA", nullptr, "STY", "STA", "STX", "BBS0",
        /*9*/ "BCC", "STA", "STA", nullptr, "STY", "STA", "STX", "SMB1", "TYA", "STA", "TXS", nullptr, "STZ", "STA", "STZ", "BBS1",
        /*A*/ "LDY", "LDA", "LDX", nullptr, "LDY", "LDA", "LDX", "SMB2", "TAY", "LDA", "TAX", nullptr, "LDY", "LDA", "LDX", "BBS2",
        /*B*/ "BCS", "LDA", "LDA", nullptr, "LDY", "LDA", "LDX", "SMB3", "CLV", "LDA", "TSX", nullptr, "LDY", "LDA", "LDX", "BBS3",
        /*C*/ "CPY", "CMP", nullptr, nullptr, "CPY", "CMP", "DEC", "SMB4", "INY", "CMP", "DEX", "WAI", "CPY", "CMP", "DEC", "BBS4",
        /*D*/ "BNE", "CMP", "CMP", nullptr, nullptr, "CMP", "DEC", "SMB5", "CLD", "CMP", "PHX", "STP", nullptr, "CMP", "DEC", "BBS5",
        /*E*/ "CPX", "SBC", nullptr, nullptr, "CPX", "SBC", "INC", "SMB6", "INX", "SBC", "NOP", nullptr, "CPX", "SBC", "INC", "BBS6",
        /*F*/ "BEQ", "SBC", "SBC", nullptr, nullptr, "SBC", "INC", "SMB7", "SED", "SBC", "PLX", nullptr, nullptr, "SBC", "INC", "BBS7"};

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

    char* opCodeName = opCodeNames[data];
    sprintf(output,
            "%d. [%c] Address: %04x Data: %02x [%s] %s %s",
            instructionCounter,
            (operation ? 'R' : 'W'),
            address,
            data,
            opCodeName != nullptr ? opCodeName : "",
            isResetSequence ? "[RST]" : "",
            (address == MP_RST_LB_ADDR || address == MP_RST_HB_ADDR) ? "[Program Counter]" : "");
    Serial.println(output);

    if(address == MP_RST_HB_ADDR) {
        isResetSequence = false;
    }

    instructionCounter++;
}

void setup() {
    Serial.begin(9600);

    pinMode(MP_RWB_PIN, INPUT);
    pinMode(MP_CLOCK_PIN, INPUT);
    pinModes(mpAddressPins, INPUT);
    pinModes(mpDataPins, INPUT);

    attachInterrupt(digitalPinToInterrupt(MP_CLOCK_PIN), onClockRisingEdge, RISING);
}

void loop() {
// write your code here
}