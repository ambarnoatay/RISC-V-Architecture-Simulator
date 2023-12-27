#ifndef DRAM_H
#define DRAM_H

#include "types.h"
#include <cstdint>
class DRAM {
public:
    DRAM() {}

    // Function to read data from DRAM
    bool readData(uint64_t address, int& data) const;

    // Function to write data to DRAM
    void writeData(uint64_t address, int data);

private:
    // Implementation details for DRAM
};

#endif  // DRAM_H
