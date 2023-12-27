#ifndef FETCH_H
#define FETCH_H
#include"types.h"
#include<vector>
class Fetch {
public:
    Fetch(std::vector<Instruction>& program);
    Instruction fetch(int ProgCount);
    void initialize();

private:
    std::vector<Instruction>& program;
    int pc;  // Program Counter
};

#endif 