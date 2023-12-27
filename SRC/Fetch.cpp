#include"Fetch.h"
#include<iostream>
Fetch::Fetch(std::vector<Instruction>& program): program(program), pc(0) {}

void Fetch::initialize()
{
    pc = 0;
    // Add more functionality here
    // For example, reset any other variables or data structures
    // Perform any necessary initialization steps
}
Instruction Fetch::fetch(int ProgCount)
{
    if(ProgCount < program.size())
    {
        printf("PC:  %d\n",ProgCount);
        
        
        return program[ProgCount];
    }
    else
    {
        return {Opcode::HALT, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0};
    }
}
