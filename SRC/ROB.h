#ifndef ROB_H
#define ROB_H
#define MAX_ROB_ENTRY 20
#include "types.h"
#include <queue>

typedef struct ROBEntry {
    ROBEntry() : valid(false), ready(false), exec(false),instruction(Opcode::NOP, -1, -1, -1, -1, 0, 0, 0, -1, -1, 0, 0, -1, -1, -1) {}

    
    bool valid;
    bool ready;
    bool exec;
    Instruction instruction;
}ROBEntry;

typedef struct ROB {
  
    
    ROBEntry robEntries[MAX_ROB_ENTRY];
    int tail;
    int head;
}ROB;
ROB*      ROB_init(void);
void      ROB_print_state(ROB *t);

bool      ROB_check_space(ROB *t);
int       ROB_insert(ROB *t, Instruction inst);
void      ROB_mark_exec(ROB *t, Instruction inst);
void      ROB_mark_ready(ROB *t, Instruction inst);
bool      ROB_check_ready(ROB *t, int tag);
bool      ROB_check_head(ROB *t);
void      ROB_wakeup(ROB *t, int tag);
Instruction ROB_remove_head(ROB *t);
void      ROB_flush(ROB *t);
    

#endif  // ROB_H
