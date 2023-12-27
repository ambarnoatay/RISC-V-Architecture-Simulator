#ifndef EXECUTE_H
#define EXECUTE_H
#define MAX_EXEC_ENTRIES 16
#include"types.h"
#include<vector>
class Execute_Entry{
public:
    Execute_Entry() : valid(false),instruction(Opcode::HALT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}

    bool isValid() const {
        return valid;
    }

    void setValid(bool value) {
        valid = value;
    }

    const Instruction& getInstruction() const {
        return instruction;
    }

    void setInstruction(const Instruction& instr) {
        instruction = instr;
    }
    void reduceInstrCycle(int t)
    {
        instruction.exe_wait_cycles -= t;
    }
    int ExecWaitCyclesLeft()
    {
        return instruction.exe_wait_cycles;
    
    }
private:
    bool valid;
    Instruction instruction;
};

class Execute {
public:
    // Execute the instruction and perform the operation
    int execute(const Instruction& instruction, int rs1, int rs2);
    void initialize();    
    void InsertQueue(const Instruction& instruction);
    void cycleExec();
    bool checkDone();
    Instruction removeInstruction();
private: 
    Execute_Entry Execute_Entries[MAX_EXEC_ENTRIES];
};
#endif