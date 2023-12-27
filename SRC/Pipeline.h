#ifndef PIPELINE_H
#define PIPELINE_H
#define MAX_WRITEBACKS 64
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <queue>
#include"types.h"
#include"Fetch.h"
#include"Decode.h"
#include"Execute.h"
#include"Schedule.h"
#include"Memory.h"
#include"Writeback.h"
#include"ROB.h"
#include"RAT.h"
#include"MemAccess.h"
class PipelineLatch {
public:
   PipelineLatch() : instruction(Opcode::HALT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
                                   valid(false),
                                   stall(false) {
    // Additional constructor logic, if needed
}



    void write(const Instruction& instr) {
        instruction = instr;
        valid = true;
        stall = false;
        
    }
    void setsrc1Tag(int tag)
    {
        instruction.src1_tag = tag;
    }
    void setsrc2Tag(int tag)
    {
        instruction.src2_tag = tag;
    }
    void setSrc1Ready()
    {
        instruction.src1_ready = true;
    }
    void setSrc2Ready()
    {
        instruction.src2_ready = true;
    }
    const Instruction& readInstruction() const {
        return instruction;
    }
    bool isStalled() const {
        return stall;
    }
    bool isValid() const {
        return valid;
    }
    void setValid(bool value) {
        valid = value;
    }
    void setStall(bool v)
    {
        stall = v;  
    }
   

private:
    Instruction instruction;
     
    bool valid;
    bool stall;
    
};

class Pipeline {
public:
    // Constructor
    Pipeline(std::vector<Instruction>& program);

    // Function to execute one cycle of the pipeline
    
    void Cycle();
    int getCycleCount() const;
    void initializePipeline();
    Fetch getFetchStage() const;
    Decode getDecodeStage() const;
    //Schedule getScheduleStage() const;
    Execute getExecuteStage() const;
    Memory getMemoryStage() const;
    WriteBack getWriteBackStage() const;
    
    
    int getInstructionCount() const;
    void FetchCycle();  
    void DecodeCycle();
    void IssueInstruction();
    void ScheduleCycle();
    void ExecuteCycle();  
    void WBCycle();
    void CommitCycle();
    int getCycleCount();
    int getIFinst();
    int getIDinst();    
    int getSCHinst();
    int getEXEinst();
    int getPC();

    void setPC(int val);
    Opcode getIFopcode();
    void printpipeROB()
    {
        rob.printROB();
    }
    void printRAT()
    {
        rat.print_state();
    }
    
private:
    // Pipeline latches
    PipelineLatch IF;  // Instruction fetched and stored for Decode stage
    PipelineLatch ID;  // Instruction decoded and stored for Schedule stage
    PipelineLatch SCH; // Instruction scheduled and stored for Execute stage
    PipelineLatch EXE[MAX_WRITEBACKS]; // Instruction after execution and stored for WriteBack stage
    PipelineLatch MEM_WB; // Instruction after memory access and stored for WriteBack stage

    // Stages of the pipeline
    Fetch fetchStage;
    Decode decodeStage;
    //Schedule scheduleStage; // Assuming a Schedule stage
    Execute executeStage;
    Memory memoryStage;
    WriteBack writeBackStage;

    ROB rob;
    RAT rat;
    int instructionCount;
    int cycleCount;
    int retired_instruction;
    int PC;
};


#endif
