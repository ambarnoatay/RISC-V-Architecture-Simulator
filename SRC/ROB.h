#ifndef ROB_H
#define ROB_H
#define MAX_ROB_ENTRY 20
#include "types.h"
#include <iostream>
class ROBEntry {
public:    
    ROBEntry()
    {
        
        valid = false;
        ready = false;
        exec = false;
        instruction = Instruction(Opcode::NOP, -1, -1, -1, -1, 0, 0, 0, -1, -1, 0, 0, -1, -1, -1);
    }
    
    Instruction getInstr()
    {
        return instruction;
    }
    bool isValid() const {
        return valid;
    }
    bool isReady() const {
        return ready;
    }
    bool isExec() const {
        return exec;
    }
    void setValid(bool value) {
        valid = value;
    }
    void setReady(bool value) {
        ready = value;
    }
    void setExec(bool value) {
        exec = value;
    }
    void setInstruction(const Instruction& instr) {
        instruction = instr;
    }
    void setSrc1Ready()
    {
        instruction.src1_ready = true;
    }
    void setSrc2Ready()
    {
        instruction.src2_ready = true;
    }
    void setTag(int tag)
    {
        instruction.destTag = tag;
    }
    bool IsSrc1Ready()
    {
        return instruction.src1_ready;
    }
    bool IsSrc2Ready()
    {
        return instruction.src2_ready;
    }
    

private:
    bool valid;
    bool ready;
    bool exec;
    Instruction instruction;
};

class ROB {
public:
    ROB()
    {
        
        tail = 0;
        head = 0;
        
        for (int i = 0; i < MAX_ROB_ENTRY; i++)
        {
            robEntries[i] = ROBEntry();
        }
    }
    void printROB()
    {
        std::cout<<"Printing ROB...\n";
        for(int i=0;i<MAX_ROB_ENTRY;i++)
        {
            std::cout<<"ROB Entry "<<i<<" Valid: "<<robEntries[i].isValid()<<" Ready: "<<robEntries[i].isReady()<<" Exec: "<<robEntries[i].isExec()<<" Instruction: "<<robEntries[i].getInstr().inst_num<<std::endl;
        }
    }
    bool CheckSpace()
    {
        if (this->tail == this->head)
        {
            if(this->robEntries[this->tail].isValid() ==false)
                return true;
            else
                return false;
        }

        
        return true;
    }
    int Insert(Instruction inst)
    {
        int tail = this->tail;
        if(this->CheckSpace())
        {
            
            this->robEntries[this->tail].setInstruction(inst);
            this->robEntries[this->tail].setValid(true);
            this->robEntries[this->tail].setReady(false);
            this->robEntries[this->tail].setExec(false);
            
            this->tail = (this->tail+1)%MAX_ROB_ENTRY;
            return tail;
        }
        else
            return -1;
    }
    void MarkExec(Instruction inst)
    {
        if(this->robEntries[inst.destTag].isValid() && !this->robEntries[inst.destTag].isExec())
        {
            this->robEntries[inst.destTag].setExec(true);
        }
    }
    void MarkReady(Instruction inst)
    {
        if(this->robEntries[inst.destTag].isValid() && !this->robEntries[inst.destTag].isReady() && this->robEntries[inst.destTag].isExec())
        {
            this->robEntries[inst.destTag].setReady(true);
        }
    }
    bool CheckReady(int tag)
    {
        if(this->robEntries[tag].isValid())
            return true;
        return false;
    }
    bool CheckHead()
    {
        
        if(this->robEntries[this->head].isValid())
            return this->robEntries[this->head].isReady();
        
        return false;
    }
    void Wakeup(int tag)
    {
        for(int i=0;i<MAX_ROB_ENTRY;i++)
        {
            if(this->robEntries[i].isValid())
            {
                if(this->robEntries[i].getInstr().src1_tag == tag)
                {
                    this->robEntries[i].setSrc1Ready();
                } 
                if(this->robEntries[i].getInstr().src2_tag == tag)
                {
                    this->robEntries[i].setSrc2Ready();
                }
            }
            
        }  
    }
    Instruction RemoveHead()
    {
        Instruction i = this->robEntries[this->head].getInstr();
        if(this->robEntries[this->head].isReady() && this->robEntries[this->head].isValid())
        {
            this->robEntries[this->head].setReady(false);
            this->robEntries[this->head].setValid(false);
            this->robEntries[this->head].setExec(false);
            this->robEntries[this->head].setInstruction(Instruction(Opcode::NOP, -1, -1, -1, -1, 0, 0, 0, -1, -1, 0, 0, -1, -1, -1));
            
            this->head =(this->head+1)%MAX_ROB_ENTRY;
            
        }
        return i; 
    }
    void Flush()
    {
        for(int i=0;i<MAX_ROB_ENTRY;i++)
        {
            this->robEntries[i].setValid(false);
            this->robEntries[i].setExec(false);
            this->robEntries[i].setReady(false);
        }
        head = 0;
        tail = 0;
        
    }

    
    void setROBTag(int tag)
    {
        this->robEntries[tag].setTag(tag);
    }
    Instruction getROBInstr(int tag)
    {
        return this->robEntries[tag].getInstr();
    }
    bool IsROBReady(int tag)
    {
        return this->robEntries[tag].isReady();
    }  
    bool IsROBValid(int tag)
    {
        return this->robEntries[tag].isValid();
    }
    bool IsROBExec(int tag)
    {
        return this->robEntries[tag].isExec();
    }
    bool IsSrc1Ready(int tag)
    {
        return this->robEntries[tag].IsSrc1Ready();
    }
    bool IsSrc2Ready(int tag)
    {
        return this->robEntries[tag].IsSrc2Ready();
    }
    void setROBValid(int tag)
    {
        this->robEntries[tag].setValid(true);
    }   


private:
    
    ROBEntry robEntries[MAX_ROB_ENTRY];
    int tail;
    int head;
};

    

#endif  // ROB_H
