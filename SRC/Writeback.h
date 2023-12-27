#ifndef WRITEBACK_H
#define WRITEBACK_H

#include "types.h"

class WriteBack {
public:
    WriteBack(){};

    // Function to execute the WriteBack stage
    void execute(Instruction& instruction, int& aluResult);
    void initialize(){};

private:
    // Simulated register file (for simplicity, using an array as the register file)
    int registerFile[32];

    // Helper function to simulate register write
    void writeRegister(int reg, int data);
};

#endif  // WRITEBACK_H
