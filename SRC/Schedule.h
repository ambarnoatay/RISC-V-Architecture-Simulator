#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "types.h"
#include"ROB.h"
#include"RAT.h"
class Schedule {
public:
    Schedule():scheduledInstruction(Opcode::HALT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {};

    // Function to perform scheduling
    void schedule(const Instruction& instr, const ROB& rob, const RAT& rat);

    // Getter for the scheduled instruction
    const Instruction& getScheduledInstruction() const;

private:
    Instruction scheduledInstruction;
};

#endif  // SCHEDULE_H
