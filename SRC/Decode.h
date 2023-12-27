#ifndef DECODE_H
#define DECODE_H
#include"types.h"
#include<vector>
// Define the Decode stage
class Decode {
public:
    // Decode the instruction and print its details
    void decode(const Instruction& instruction);
    void initialize();
};
#endif