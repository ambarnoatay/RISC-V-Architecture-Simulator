#include"WriteBack.h"
#include<algorithm>
#include<iostream>
WriteBack::WriteBack() {
    // Initializing the simulated register file with zeros
    std::fill(registerFile, registerFile+32, 0);
}
void WriteBack::initialize() {
    // Initialize the write back stage
    std::fill(registerFile, registerFile+32, 0);
}
void WriteBack::execute(Instruction& instruction, int& aluResult) {
    // Check if the instruction writes to a register
    if (instruction.opcode != Opcode::SW && instruction.opcode != Opcode::BEQ && instruction.opcode != Opcode::HALT) {
        // Write the ALU result back to the register file
        writeRegister(instruction.rd, aluResult);
    }
}

void WriteBack::writeRegister(int reg, int data) {
    // Simulated register write operation
    if (reg >= 0 && reg < 32) {
        registerFile[reg] = data;
    } else {
        // Handle invalid register index
        std::cerr << "Invalid register index: " << reg << std::endl;
    }
}
