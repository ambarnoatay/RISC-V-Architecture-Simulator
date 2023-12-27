#include "MemAccess.h"

MemAccess::MemAccess(int l1Size, int l1Associativity, int l2Size, int l2Associativity)
    : l1Cache(l1Size, l1Associativity),
      l2Cache(l2Size, l2Associativity) {
    // Initialize other members if needed
}

bool MemAccess::readMemory(uint64_t address, int& data) {
    // Implement memory read logic using L1 cache, L2 cache, and DRAM
    // You may implement a hierarchy (L1 -> L2 -> DRAM) or other policies
    // based on your specific requirements
    return false; // Placeholder value
}

void MemAccess::writeMemory(uint64_t address, int data) {
    // Implement memory write logic using L1 cache, L2 cache, and DRAM
    // You may implement a hierarchy (L1 -> L2 -> DRAM) or other policies
    // based on your specific requirements
}
