#include"Decode.h"
#include<iostream>

void Decode::initialize()
{
    // Initialize the decode stage
    
}

void Decode::decode(const Instruction& instruction)
{
    switch (instruction.opcode) 
    {
        case Opcode::ADD:
            std::cout << "ADD ";
            break;
        case Opcode::SUB:
            std::cout << "SUB ";
            break;
        case Opcode::LW:
            std::cout << "LW ";
            break;
        case Opcode::SW:
            std::cout << "SW ";
            break;
        case Opcode::BEQ:
            std::cout << "BEQ ";
            break;
        case Opcode::JAL:
            std::cout << "JAL ";
            break;
        case Opcode::HALT:
            std::cout << "HALT ";
            break;
        default:
            std::cout << "Unknown Opcode ";
            break;
    }

    std::cout << "rd=" << instruction.rd << " rs1=" << instruction.rs1 << " rs2=" << instruction.rs2
            << " imm=" << instruction.imm << std::endl;
}
