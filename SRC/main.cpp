#include <iostream>
#include <vector>
#include"types.h"
#include"Fetch.h"
#include"Decode.h"
#include"Execute.h"
#include<random>
#include"Pipeline.h"
using namespace std;
int SCHED_POLICY = 0;
Opcode getRandomOpcode() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // List of all opcodes
    std::vector<Opcode> allOpcodes = {
        Opcode::ADD,
        Opcode::SUB,
        Opcode::LW,
        Opcode::SW,
        Opcode::BEQ,
        Opcode::JAL,
        
    };

    std::uniform_int_distribution<std::size_t> dis(0, allOpcodes.size() - 1);
    return allOpcodes[dis(gen)];
}
int getRandomInt(int min, int max) 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(min, max);

    return dis(gen);
}

int get_exe_wait_cycles(Opcode op) {
    switch (op) {
        case Opcode::ADD:
        case Opcode::SUB:
            return 1;
        case Opcode::LW:
        case Opcode::SW:
            return 2;
        case Opcode::BEQ:
            return 3;
        case Opcode::JAL:
            return 4;
        default:
            return 0;
    }
}
int main() {
    // Example RISC-V program
    vector<Instruction> program;
    for(int i=0;i<100;i++)
    {
        Opcode op = getRandomOpcode();
        int rd = getRandomInt(0, 31), rs1 = getRandomInt(-1, 31), rs2 = getRandomInt(-1, 31), imm = getRandomInt(0, 100);

        Instruction instr = {op, rd, rs1, rs2, imm,
                            true, rs1==-1?false:true, rs2==-1?false:true, -1,-1,rs1==-1?false:true, rs2==-1?false:true,-1,i+1,get_exe_wait_cycles(op)};
        program.push_back(instr);
        
    }
    Instruction haltfunc = {Opcode::HALT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    program.push_back(haltfunc);
    for(auto it:program)
    {
       printf("OP: %d Rd: %d Rs1: %d Rs2: %d EXECycles: %d  \n",it.opcode,it.rd,it.rs1,it.rs2,get_exe_wait_cycles(it.opcode));
    }
    // Initialize Fetch, Decode, and Execute stages
    Pipeline pipeline(program);
    //pipeline.pipe_init();
    pipeline.Cycle();
    // Execute the pipeline
    while (pipeline.getIFopcode() != Opcode::HALT &&  pipeline.getIFinst()!=0) {
        printf("IF: %d ID: %d SCH : %d EX: %d \n",pipeline.getIFinst(),pipeline.getIDinst(),pipeline.getSCHinst(),pipeline.getEXEinst());
        pipeline.printpipeROB();   
        pipeline.printRAT(); 
        pipeline.Cycle();
        if(pipeline.getCycleCount()>200)
        {
            cout<<"Pipeline is Dying"<<endl;
            break;
        }
    }

    return 0;
}