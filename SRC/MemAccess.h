#ifndef MEM_ACCESS_H
#define MEM_ACCESS_H

#include "types.h"
#include "Cache.h"
#include "DRAM.h"

class MemAccess {
public:
    MemAccess(int l1Size, int l1Associativity, int l2Size, int l2Associativity);

    // Function to perform memory read
    bool readMemory(uint64_t address, int& data);

    // Function to perform memory write
    void writeMemory(uint64_t address, int data);

private:
    Cache l1Cache;
    Cache l2Cache;
    DRAM dram;
};

#endif  // MEM_ACCESS_H
