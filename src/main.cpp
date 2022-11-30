#include <Arduino.h>
#include "utils.h"
#include "opcodes.h"
#include "RingBuf.h"
#include "structures.h"
#include "instruction_tracker.h"
#include "macros.h"

using namespace itsgosho;

int mpAddressPins[16] = {MP_A0_PIN, MP_A1_PIN, MP_A2_PIN, MP_A3_PIN, MP_A4_PIN, MP_A5_PIN, MP_A6_PIN, MP_A7_PIN, MP_A8_PIN, MP_A9_PIN, MP_A10_PIN, MP_A11_PIN, MP_A12_PIN, MP_A13_PIN, MP_A14_PIN, MP_A15_PIN};
int mpDataPins[8] = {MP_D0_PIN, MP_D1_PIN, MP_D2_PIN, MP_D3_PIN, MP_D4_PIN, MP_D5_PIN, MP_D6_PIN, MP_D7_PIN};

RingBuf* buf = RingBuf_new(sizeof(struct MicroprocessorRead), MP_READ_BUFF_SIZE);

void onClockRisingEdge() {
    bool operation = digitalRead(MP_RWB_PIN);
    unsigned short int address = digitalRead(mpAddressPins, LSBFIRST);
    unsigned short int data = digitalRead(mpDataPins, LSBFIRST);

    MicroprocessorRead microprocessorRead = {operation, address, data};
    buf->add(buf, &microprocessorRead);
}

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println("To get information about the instructions, please reset the microprocessor!");

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

uint16_t lineCounter = 1;
bool isResetSequence = false;
InstructionTracker instructionTracker{};

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

    if (address == MP_RST_SEQ_ADDR) {
        lineCounter = 1;
        isResetSequence = true;
    }

    instructionTracker.read(microprocessorRead);

    String instructionName = getInstructionName(instructionTracker.getCurrentInstruction());
    String addressingModeSymbol = getAddressingModeSymbol(instructionTracker.getCurrentAddressingMode());
    int instructionSequenceCounter = instructionTracker.getInstructionSequenceCounter();
    int instructionSequenceRequired = instructionTracker.getInstructionSequenceRequired();

    char operationPrint = operation ? 'R' : 'W';
    String operationDirectionPrint = operation ? "<-" : "->";;
    String opCodePrint = instructionTracker.getHasCurrentInstruction() ? "[" + instructionName + " ; " + addressingModeSymbol + " ; " + instructionSequenceCounter + "/" + instructionSequenceRequired + "]" : "";

    char output[100];
    sprintf(output,
            "%03u. [%c] (Address: %04x ; %05u %s Data: %02x ; %03u) %s %s %s",
            lineCounter,
            operationPrint,
            address,
            address,
            operationDirectionPrint.begin(),
            data,
            data,
            opCodePrint.begin(),
            isResetSequence ? "[Resetting]" : "",
            address == MP_RST_LB_ADDR ? "[Program Counter: Low Byte]" : (address == MP_RST_HB_ADDR ? "[Program Counter: High Byte]" : ""));
    Serial.println(output);

    if (address == MP_RST_HB_ADDR) {
        isResetSequence = false;
    }

    lineCounter++;
}