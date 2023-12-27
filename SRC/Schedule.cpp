#include "Schedule.h"

void Schedule::schedule(const Instruction& instr, const ROB& rob, const RAT& rat) {
    // Implement your scheduling logic here
    // You can use information from the instruction, ROB, and RAT to determine the schedule
    // For simplicity, let's assume no scheduling and directly pass the instruction
    scheduledInstruction = instr;
}

const Instruction& Schedule::getScheduledInstruction() const {
    return scheduledInstruction;
}
