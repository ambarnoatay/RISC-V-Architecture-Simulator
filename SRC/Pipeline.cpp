#include "Pipeline.h"
#include "ROB.h" // Add missing include statement for ROB.h
#include "RAT.h"

extern int SCHED_POLICY;

Pipeline::Pipeline(std::vector<Instruction>& program) : cycleCount(0),
                       fetchStage(program),  // Initialize fetch stage
                       decodeStage(), // Initialize decode stage
                       executeStage(),// Initialize execute stage
                       memoryStage(), // Initialize memory stage
                       writeBackStage() // Initialize write back stage
                        

                        

{
    
    rob = ROB();
    rat = RAT();
    instructionCount = 0;

}
Fetch Pipeline::getFetchStage() const
{
    return fetchStage;
}
Decode Pipeline::getDecodeStage() const
{
    return decodeStage;
}
Execute Pipeline::getExecuteStage() const
{
    return executeStage;
}
Memory Pipeline::getMemoryStage() const
{
    return memoryStage;
}
WriteBack Pipeline::getWriteBackStage() const
{
    return writeBackStage;
}



int Pipeline::getInstructionCount() const
{
    return instructionCount;
}


void Pipeline::Cycle() {
    // Execute each stage in reverse order to simulate a pipeline
    //printf("ROB num: %d\n",this->rob->numROBs());
    printpipeROB();
    ++cycleCount;
    printf("Cycle %d\n",cycleCount);
    CommitCycle();
    printf("Commit Cycle Done\n");
    WBCycle();
    printf("WB Cycle Done\n");
    ExecuteCycle(); 
    printf("Execute Cycle Done\n");
    ScheduleCycle();    
    printf("Schedule Cycle Done\n");
    IssueInstruction(); 
    printf("Issue Instruction Done\n");
    DecodeCycle();
    printf("Decode Cycle Done\n");
    FetchCycle();
    printf("Fetch Cycle Done\n");
    
}
int Pipeline::getCycleCount() const
{
    return cycleCount;
}

void Pipeline::initializePipeline()
{
    cycleCount = 0;
    // Initialize other pipeline values here
    // For example:
    this->fetchStage.initialize(); // Initialize fetch stage
    decodeStage.initialize(); // Initialize decode stage
    executeStage.initialize(); // Initialize execute stage
    memoryStage.initialize(); // Initialize memory stage
    writeBackStage.initialize(); // Initialize write back stage
}

void Pipeline::FetchCycle()
{
    PipelineLatch FE_latch;
    
    if(!this->IF.isStalled() && !this->IF.isValid())//No Stall and latch empty
    {
        Instruction fetched = this->fetchStage.fetch(this->PC);
        if(fetched.opcode != Opcode::HALT)
        {
            this->IF.write(fetched);
            this->PC+=1;
            printf("Instruction %d fetched\n",this->IF.readInstruction().inst_num);
            return;
        }
        else
        {
            IF.write(fetched);
            printf("HALT Instruction fetched\n");
            return;
        }
        
    }
    
}
void Pipeline::DecodeCycle()
{
    if(!this->ID.isStalled() && !this->ID.isValid())//No Stall and latch empty
    {
        this->ID.write(this->IF.readInstruction());
        this->IF.setValid(false);
        printf("Instruction %d decoded\n",this->ID.readInstruction().inst_num);
    }
}
void Pipeline::IssueInstruction()
{
    printf("Instruction in issue %d\n",this->ID.readInstruction().inst_num);
    if(this->ID.isValid() && this->ID.readInstruction().inst_num!=0)
    {
        int src1 = this->rat.get_remap(this->ID.readInstruction().rs1);
        int src2 = this->rat.get_remap(this->ID.readInstruction().rs2);
        int immval = this->ID.readInstruction().imm;
        if(src1!=-1 && this->ID.readInstruction().rs1!=-1)//if src1 is not -1 and src1_reg is not -1
            this->ID.setsrc1Tag(src1);
        else
            this->ID.setsrc1Tag(-1);
        if(src2!=-1 && this->ID.readInstruction().rs2!=-1)//if src2 is not -1 and src2_reg is not -1
            this->ID.setsrc2Tag(src2);
        else
            this->ID.setsrc2Tag(-1);
        if(this->ID.readInstruction().rs1 == -1 || src1 == -1 || this->rob.IsROBReady(this->ID.readInstruction().src1_tag))
            this->ID.setSrc1Ready();
        if(this->ID.readInstruction().rs2 == -1 || src2 == -1 || this->rob.IsROBReady(this->ID.readInstruction().src2_tag))
            this->ID.setSrc2Ready();
        if(this->rob.CheckSpace() && this->ID.readInstruction().inst_num!=0)
        {
            int tag = this->rob.Insert(this->ID.readInstruction());
            this->rob.setROBTag(tag);
            //this->rob->robEntries[tag].instruction.destTag = tag;
            this->ID.setValid(false);
            if(this->ID.readInstruction().rd != -1 && !this->rat.isRATvalid(this->ID.readInstruction().rd))
                this->rat.set_remap(this->ID.readInstruction().rd,tag);
                //RAT_set_remap(this->rat,this->ID.readInstruction().rd,tag);
            printf("Instruction %d issued\n",this->rob.getROBInstr(tag).inst_num);
        }
        

    }
    this->ID.setValid(false);
}
int last_inst = 0;
bool flag= false;
void Pipeline::ScheduleCycle()
{   
    
    if(SCHED_POLICY==0)//Inorder
    {
        Instruction ROBInstr;
        for(int j=0;j<MAX_ROB_ENTRY;j++)
        {
            if(this->rob.IsROBValid(j) && !this->rob.IsROBExec(j))
            {

                ROBInstr = this->rob.getROBInstr(j);
                //printf("Instruction in ROB: %d SRC1Ready: %d SRC2Ready: %d\n",ROBInstr.inst_num,ROBInstr.src1_ready,ROBInstr.src2_ready);
                //printf("ROBINSTR: %d opcode: %d rd: %d rs1 = %d rs2 = %d   \n",ROBInstr.inst_num,ROBInstr.opcode,ROBInstr.rd,ROBInstr.rs1,ROBInstr.rs2);
                if(!ROBInstr.src1_ready || !ROBInstr.src2_ready)
                    break;
                last_inst = ROBInstr.inst_num;
                flag = true;

                break;
            }
        } 
        if(!this->SCH.isValid() && flag)//Schedule Instruction
        {
            this->SCH.write(ROBInstr);
            if(ROBInstr.inst_num!=0)
                this->SCH.setValid(true);
            this->rob.MarkExec(ROBInstr);
            printf("Instruction %d scheduled\n",ROBInstr.inst_num);
            flag = false;
        }
    }
    else//Out of order
    {
        int fl = false;
        Instruction ROBInstr;
        for(int j=0;j<MAX_ROB_ENTRY;j++)
        {
            if(this->rob.IsROBValid(j) && !this->rob.IsROBExec(j) && this->rob.IsSrc1Ready(j) && this->rob.IsSrc2Ready(j))
            {
                ROBInstr = this->rob.getROBInstr(j);
                fl = true;
                break;
            }
        }
        if(this->SCH.isValid()&&fl)
        {
            if(ROBInstr.src1_ready && ROBInstr.src2_ready)
            {
                this->SCH.write(ROBInstr);
                this->SCH.setValid(true);
                this->rob.MarkExec(ROBInstr);
                fl = false;
            }
        }
    }
    
}

void Pipeline::ExecuteCycle()
{
    if(this->SCH.isValid())
    {
        this->executeStage.InsertQueue(this->SCH.readInstruction());
        this->SCH.setValid(false);
    }
    this->executeStage.cycleExec();
    for(int idx =0;idx<MAX_WRITEBACKS;idx++)
    {
        if(this->executeStage.checkDone())
        {
            this->EXE[idx].setStall(false);
            this->EXE[idx].setValid(true);
            this->EXE[idx].write(this->executeStage.removeInstruction());
            printf("Instruction %d executed\n",this->EXE[idx].readInstruction().inst_num);
        }
        else
            break;
    }

}
void Pipeline::WBCycle()
{
    for(int idx =0;idx<MAX_EXEC_ENTRIES;idx++)
    {
        if(this->EXE[idx].isValid())
        {
            Instruction instr = this->EXE[idx].readInstruction();

            this->rob.Wakeup(instr.destTag);
            //ROB_wakeup(this->rob,instr.destTag);
            this->rob.MarkExec(instr);
            //ROB_mark_ready(this->rob,instr);    
            this->EXE[idx].setValid(false);
            printf("Instruction %d completed\n",instr.inst_num);
        }
    }

}

void Pipeline::CommitCycle()
{
    
    if(this->rob.CheckHead())   
    {
        
        Instruction instr = this->rob.RemoveHead();
        this->rat.reset_entry(instr.rd);
        //RAT_reset_entry(this->rat,instr.rd);
        this->retired_instruction+=1;
        printf("Instruction %d committed\n",instr.inst_num);
    }
}
int Pipeline::getCycleCount() 
{
    return this->cycleCount;
}
int Pipeline::getIFinst()
{
    return this->IF.readInstruction().inst_num;
}
int Pipeline::getIDinst()
{
    return this->ID.readInstruction().inst_num;
}
int Pipeline::getSCHinst()
{
    return this->SCH.readInstruction().inst_num;
}
int Pipeline::getEXEinst()
{
    return this->EXE[0].readInstruction().inst_num;
}
int Pipeline::getPC()
{
    return this->PC;
}
void Pipeline::setPC(int val)
{
    this->PC = val;
}
Opcode Pipeline::getIFopcode()
{
    return this->IF.readInstruction().opcode;
}
