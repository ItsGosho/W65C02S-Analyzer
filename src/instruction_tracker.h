#ifndef W65C02S_ANALYZER_INSTRUCTION_TRACKER_H
#define W65C02S_ANALYZER_INSTRUCTION_TRACKER_H

#include "opcodes.h"
#include "structures.h"
#include "macros.h"

using namespace itsgosho;

namespace itsgosho {

    class InstructionTracker {

    public:
        InstructionTracker();

        void read(const MicroprocessorRead& microprocessorRead);

        Instruction getCurrentInstruction() const;

        AddressingMode getCurrentAddressingMode() const;

        int getInstructionSequenceCounter() const;

        int getInstructionSequenceRequired() const;

        bool getHasCurrentInstruction() const;

    private:
        Instruction currentInstruction;
        AddressingMode currentAddressingMode;
        int instructionSequenceCounter;
        int instructionSequencesRequired;
        bool hasCurrentInstruction;
        bool isResetSequencePassed;

        bool isInstructionEnd();

        bool isInstructionStart(const MicroprocessorRead& microprocessorRead);
    };
}

#endif
