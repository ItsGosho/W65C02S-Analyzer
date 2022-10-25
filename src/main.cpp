#include <Arduino.h>
#include "utils.h"
#include "opcodes.h"
#include "RingBuf.h"

using namespace itsgosho;

#define BAUD_RATE 9600
#define MP_READ_BUFF_SIZE 20

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

struct MicroprocessorRead {
    bool operation;
    unsigned short int address;
    unsigned short int data;
};

RingBuf* buf = RingBuf_new(sizeof(struct MicroprocessorRead), MP_READ_BUFF_SIZE);

volatile uint16_t instructionCounter = 1;
volatile bool isResetSequence = false;

void onClockRisingEdge() {
    bool operation = digitalRead(MP_RWB_PIN);
    unsigned short int address = digitalRead(mpAddressPins, LSBFIRST);
    unsigned short int data = digitalRead(mpDataPins, LSBFIRST);

    MicroprocessorRead microprocessorRead = {operation, address, data};
    buf->add(buf, &microprocessorRead);
}

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println("The address and data are displayed in hexadecimal ; decimal format!");

    pinMode(MP_RWB_PIN, INPUT);
    pinMode(MP_CLOCK_PIN, INPUT);
    pinModes(mpAddressPins, INPUT);
    pinModes(mpDataPins, INPUT);

    attachInterrupt(digitalPinToInterrupt(MP_CLOCK_PIN), onClockRisingEdge, RISING);
}

MicroprocessorRead pullMicroprocessorRead() {
    struct MicroprocessorRead microprocessorRead{};

    buf->pull(buf, &microprocessorRead);

    return microprocessorRead;
}

template<typename T>
String toBinary(T value) {

    char dataBinary[sizeof(T) * 8 + 1];
    ltoa(value, dataBinary, 2);

    return dataBinary;
}

void loop() {

    if (buf->isEmpty(buf))
        return;

    if (buf->isFull(buf)) {
        Serial.println("Can't keep up with the clock! Increase your buffer's size from the MP_READ_BUFF_SIZE macro!");
    }

    MicroprocessorRead microprocessorRead = pullMicroprocessorRead();

    bool operation = microprocessorRead.operation;
    unsigned short int address = microprocessorRead.address;
    unsigned short int data = microprocessorRead.data;

    toBinary(address);

    OpCode opCodeAddress = opCodes[data];

    if (address == MP_RST_SEQ_ADDR) {
        instructionCounter = 1;
        isResetSequence = true;
    }

    if (instructionCounter > MP_RST_INST_COUNT)
        isResetSequence = false;

    String opCode = "[" + getInstructionName(opCodeAddress.instruction) + " ; " + getAddressingModeSymbol(opCodeAddress.addressingMode) + "]";

    char output[100];

    sprintf(output,
            "%03u. [%c] (Address: %04x ; %05u ; %s %s Data: %02x ; %03u ; %s) %s %s %s",
            instructionCounter,
            (operation ? 'R' : 'W'),
            address,
            address,
            toBinary(address).begin(),
            (operation ? "<-" : "->"),
            data,
            data,
            toBinary(data).begin(),
            !isResetSequence && opCodeAddress.hasOpCode ? opCode.begin() : "",
            isResetSequence ? "[Resetting]" : "",
            address == MP_RST_LB_ADDR ? "[Program Counter: Low Byte]" : (address == MP_RST_HB_ADDR ? "[Program Counter: High Byte]" : ""));
    Serial.println(output);

    instructionCounter++;
}