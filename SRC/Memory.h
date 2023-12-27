#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"
#include<vector>
class Memory {
public:
    Memory(){};

    // Function to execute the Memory stage
    void execute(Instruction& instruction, int& aluResult, int& memoryData);
    void initialize(){};

private:
    // Simulated memory (for simplicity, using a vector as memory)
    std::vector<int> memory;

    // Helper function to simulate memory read
    int readMemory(int address);

    // Helper function to simulate memory write
    void writeMemory(int address, int data);
};

#endif  // MEMORY_H
