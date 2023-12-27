#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <cstdint>  // Include this for uint64_t
#include "types.h"

class Cache {
public:
    Cache(int size, int associativity);

    // Function to read data from the cache
    bool readData(uint64_t address, int& data) const;

    // Function to write data to the cache
    void writeData(uint64_t address, int data);

private:
    int size;            // Cache size in bytes
    int associativity;   // Cache associativity
    int blockSize;       // Cache block size
    int numSets;         // Number of sets in the cache
    std::unordered_map<uint64_t, int> cacheData;  // Cache data storage
    
    // Other necessary members and functions for cache implementation
};

#endif  // CACHE_H
