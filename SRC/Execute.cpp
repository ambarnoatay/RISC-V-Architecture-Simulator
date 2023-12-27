#include"Execute.h"
#include<iostream>

void Execute::initialize() 
{
    // Initialize the necessary members
    
}
int Execute::execute(const Instruction& instruction, int rs1, int rs2) 
{
    switch (instruction.opcode) 
    {
        case Opcode::ADD:
            return rs1 + rs2;
        case Opcode::SUB:
            return rs1 - rs2;
        case Opcode::LW:
            // Implement the logic for LW (Load Word)
            // For simplicity, let's return the sum of rs1 and imm
            return rs1 + instruction.imm;
        case Opcode::SW:
            // Implement the logic for SW (Store Word)
            // For simplicity, let's return the product of rs1 and rs2
            return rs1 * rs2;
        case Opcode::BEQ:
            // Implement the logic for BEQ (Branch Equal)
            // For simplicity, let's return 1 if rs1 is equal to rs2, 0 otherwise
            return (rs1 == rs2) ? 1 : 0;
        case Opcode::JAL:
            // Implement the logic for JAL (Jump and Link)
            // For simplicity, let's return the difference between rs1 and rs2
            return rs1 - rs2;
        // Handle other operations as needed
        default:
            std::cout << "Unsupported operation in Execute stage." << std::endl;
            return 0;  // Returning 0 for simplicity
    }
}

void Execute::InsertQueue(const Instruction& instruction)
{
    for(int i=0;i<MAX_EXEC_ENTRIES;i++)
    {
        if(!Execute_Entries[i].isValid())
        {
            Execute_Entries[i].setValid(true);
            Execute_Entries[i].setInstruction(instruction);
            break;
        }
        //MemoryAccess;
    }
}

void Execute::cycleExec()
{
    for(int i=0;i<MAX_EXEC_ENTRIES;i++)
    {
        if(Execute_Entries[i].isValid())
        {
            this->Execute_Entries[i].reduceInstrCycle(1);
        }
    }
}
bool Execute::checkDone()
{
    for(int i=0;i<MAX_EXEC_ENTRIES;i++)
    {
        if(Execute_Entries[i].isValid())
        {
            if(Execute_Entries[i].ExecWaitCyclesLeft() == 0)
            {
                return true;
            }
        }
    }
    return false;
}
Instruction Execute::removeInstruction()
{
    Instruction temp;
    for(int i=0;i<MAX_EXEC_ENTRIES;i++)
    {
        if(Execute_Entries[i].isValid())
        {
            if(Execute_Entries[i].ExecWaitCyclesLeft() == 0)
            {
                
                Execute_Entries[i].setValid(false);
                return Execute_Entries[i].getInstruction();
                
            }
        }
    }
    printf("ERROR: Trying to remove entry from empty EXEQ. Dying...\n");
    exit(-1);
    return temp;
}