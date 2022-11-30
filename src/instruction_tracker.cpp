#include "instruction_tracker.h"

using namespace itsgosho;

InstructionTracker::InstructionTracker() {
    this->instructionSequenceCounter = 0;
    this->instructionSequencesRequired = 0;
    this->hasCurrentInstruction = false;
    this->isResetSequencePassed = false;
}


void InstructionTracker::read(const MicroprocessorRead& microprocessorRead) {
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

Instruction InstructionTracker::getCurrentInstruction() const {
    return this->currentInstruction;
}

AddressingMode InstructionTracker::getCurrentAddressingMode() const {
    return this->currentAddressingMode;
}

int InstructionTracker::getInstructionSequenceCounter() const {
    return this->instructionSequenceCounter;
}

int InstructionTracker::getInstructionSequenceRequired() const {
    return this->instructionSequencesRequired;
}

bool InstructionTracker::getHasCurrentInstruction() const {
    return this->hasCurrentInstruction;
}

bool InstructionTracker::isInstructionEnd() {
    return this->isResetSequencePassed && this->hasCurrentInstruction && this->instructionSequenceCounter >= this->instructionSequencesRequired;
}

bool InstructionTracker::isInstructionStart(const MicroprocessorRead& microprocessorRead) {
    return this->isResetSequencePassed && !this->hasCurrentInstruction && microprocessorRead.operation == MP_R;
}