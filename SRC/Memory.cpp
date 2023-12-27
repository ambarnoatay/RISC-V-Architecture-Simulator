#include "Memory.h"

Memory::Memory() : memory(1024, 0) {}  // Initializing a vector of size 1024 for simplicity

void Memory::initialize() {
    // Initialize memory here
    // For example:
    memory.clear();
    memory.resize(1024, 0);
}
void Memory::execute(Instruction& instruction, int& aluResult, int& memoryData) {
    switch (instruction.opcode) {
        case Opcode::LW:
            memoryData = readMemory(aluResult);
            break;
        case Opcode::SW:
            writeMemory(aluResult, memoryData);
            break;
        default:
            // No memory operation for other opcodes
            break;
    }
}

int Memory::readMemory(int address) {
    // Simulated memory read operation
    return memory[address];
}

void Memory::writeMemory(int address, int data) {
    // Simulated memory write operation
    memory[address] = data;
}
