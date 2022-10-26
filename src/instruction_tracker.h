#ifndef W65C02S_ANALYZER_INSTRUCTION_TRACKER_H
#define W65C02S_ANALYZER_INSTRUCTION_TRACKER_H

#include "structures.h"
#include "macros.h"

using namespace itsgosho;

class InstructionTracker {

public:
    InstructionTracker() {
        this->instructionSequenceCounter = 0;
        this->instructionSequencesRequired = 0;
        this->hasCurrentInstruction = false;
        this->isResetSequencePassed = false;
    }

    void read(const MicroprocessorRead& microprocessorRead) {
        OpCode opCode = opCodes[microprocessorRead.data];

        if (this->isInstructionEnd()) {
            this->instructionSequenceCounter = 0;
            this->instructionSequencesRequired = 0;
            this->hasCurrentInstruction = false;
        }

        if (this->hasCurrentInstruction) {
            this->instructionSequenceCounter++;
        }

        if (this->isInstructionStart(microprocessorRead)) {
            this->currentInstruction = opCode.instruction;
            this->currentAddressingMode = opCode.addressingMode;
            this->hasCurrentInstruction = true;
            this->instructionSequencesRequired = getAddressingModeClockCycles(opCode.addressingMode);
            this->instructionSequenceCounter++;
        }

        if (microprocessorRead.address == MP_RST_HB_ADDR) {
            this->isResetSequencePassed = true;
        }
    }

    Instruction getCurrentInstruction() const {
        return this->currentInstruction;
    }

    AddressingMode getCurrentAddressingMode() const {
        return this->currentAddressingMode;
    }

    int getInstructionSequenceCounter() const {
        return this->instructionSequenceCounter;
    }

    int getInstructionSequenceRequired() const {
        return this->instructionSequencesRequired;
    }

    bool getHasCurrentInstruction() const {
        return this->hasCurrentInstruction;
    }

private:
    Instruction currentInstruction;
    AddressingMode currentAddressingMode;
    int instructionSequenceCounter;
    int instructionSequencesRequired;
    bool hasCurrentInstruction;
    bool isResetSequencePassed;

    bool isInstructionEnd() {
        return this->isResetSequencePassed && this->hasCurrentInstruction && this->instructionSequenceCounter >= this->instructionSequencesRequired;
    }

    bool isInstructionStart(const MicroprocessorRead& microprocessorRead) {
        return this->isResetSequencePassed && !this->hasCurrentInstruction && microprocessorRead.operation == MP_R;
    }
};

#endif
