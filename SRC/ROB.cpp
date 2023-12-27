#include "ROB.h"
#include<iostream>

ROB* ROB_init(void){
  int ii;
  ROB *t = (ROB *) calloc (1, sizeof (ROB));
  for(ii=0; ii<MAX_ROB_ENTRY; ii++){
    t->robEntries[ii].valid=false;
    t->robEntries[ii].ready=false;
    t->robEntries[ii].exec=false;
  }
  t->head=0;
  t->tail=0;
  return t;
}

/////////////////////////////////////////////////////////////
// Print State
/////////////////////////////////////////////////////////////
void ROB_print_state(ROB *t){
 int ii = 0;
  printf("Printing ROB \n");
  printf("Entry  Inst   Valid   Ready Exec\n");
  for(ii = 0; ii < MAX_ROB_ENTRY; ii++) {
    printf("%5d ::  %d\t", ii, (int)t->robEntries[ii].instruction.inst_num);
    printf(" %5d\t", t->robEntries[ii].valid);
    printf(" %5d\t", t->robEntries[ii].ready);
    printf(" %5d\n", t->robEntries[ii].exec);
  }
  printf("\n");
}

/////////////////////////////////////////////////////////////
// If there is space in ROB return true, else false
/////////////////////////////////////////////////////////////

bool ROB_check_space(ROB *t){
if (t->tail == t->head)
{
  if(t->robEntries[t->tail].valid ==false)
    return true;
  else
    return false;
}
 
return true;
}

/////////////////////////////////////////////////////////////
// insert entry at tail, increment tail (do check_space first)
/////////////////////////////////////////////////////////////

int ROB_insert(ROB *t, Instruction inst){
  
int tail = t->tail;
if(ROB_check_space(t))
{
  t->robEntries[t->tail].instruction = inst;
  t->robEntries[t->tail].valid = true;
  //t->robEntries[t->tail].instruction.destTag = t->tail;
  t->tail = (t->tail + 1)%MAX_ROB_ENTRY;

}
//printf("TAIL: %d END: %d \n",tail,t->tail);
return tail;




}

/////////////////////////////////////////////////////////////
// When an inst gets scheduled for execution, mark exec
/////////////////////////////////////////////////////////////

void ROB_mark_exec(ROB *t, Instruction inst){
  bool p1,p2;
  
  p1 = inst.src1_ready;
  
  p2 = inst.src2_ready;

  //std::cout<<"MARK EXEC INSTR#: "<<inst.instruction_num<<" exec: "<<t->robEntries[inst.destTag].exec<<" valid ROB: "<<t->robEntries[inst.destTag].valid<<" src1 ready: "<<p1<<" src2 ready: "<<p2<<'\n';
  if(!t->robEntries[inst.destTag].exec && t->robEntries[inst.destTag].valid)
    {
      //std::cout<<"MARKING EXEC: "<<inst.instruction_num<<'\n';
      t->robEntries[inst.destTag].exec = true; 
    }
}


/////////////////////////////////////////////////////////////
// Once an instruction finishes execution, mark rob entry as done
/////////////////////////////////////////////////////////////

void ROB_mark_ready(ROB *t, Instruction inst){
  bool c = t->robEntries[inst.destTag].valid && t->robEntries[inst.destTag].exec;
  if(!t->robEntries[inst.destTag].ready && c)
    t->robEntries[inst.destTag].ready = true;

}

/////////////////////////////////////////////////////////////
// Find whether the prf (rob entry) is ready
/////////////////////////////////////////////////////////////

bool ROB_check_ready(ROB *t, int tag){
  if(t->robEntries[tag].valid)
    return t->robEntries[tag].ready;
  return false;
}


/////////////////////////////////////////////////////////////
// Check if the oldest ROB entry is ready for commit
/////////////////////////////////////////////////////////////

bool ROB_check_head(ROB *t){
  if(t->robEntries[t->head].valid)
    return ROB_check_ready(t,t->head);
  return false;

}

/////////////////////////////////////////////////////////////
// For writeback of freshly ready tags, wakeup waiting inst
/////////////////////////////////////////////////////////////

void  ROB_wakeup(ROB *t, int tag){ 
  for(int i=0;i<MAX_ROB_ENTRY;i++)
  {
    if(t->robEntries[i].valid)
    {
      if(t->robEntries[i].instruction.src1_tag == tag)
      {
        t->robEntries[i].instruction.src1_ready = true;
      } 
      if(t->robEntries[i].instruction.src2_tag == tag)
      {
          t->robEntries[i].instruction.src2_ready = true;
      }
    }
    
  }  
}


/////////////////////////////////////////////////////////////
// Remove oldest entry from ROB (after ROB_check_head)
/////////////////////////////////////////////////////////////

Instruction ROB_remove_head(ROB *t){
  Instruction i = t->robEntries[t->head].instruction;
  if(t->robEntries[t->head].ready && t->robEntries[t->head].valid)
  {
    t->robEntries[t->head].ready = false;
    t->robEntries[t->head].valid = false;
    t->robEntries[t->head].exec = false;
    t->robEntries[t->head].instruction.inst_num = 0;
    
    t->head =(t->head+1)%MAX_ROB_ENTRY;
    
  }
  return i; 
}
  


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// Invalidate all entries in ROB
/////////////////////////////////////////////////////////////

void ROB_flush(ROB *t){
for(int i = 0;i<MAX_ROB_ENTRY;i++)
{
  t->robEntries[i].valid = false;
  t->robEntries[i].exec = false;
  t->robEntries[i].ready = false;
  

}
t->tail = 0;
t->head = 0;
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////