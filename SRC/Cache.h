#ifndef CACHE_H
#define CACHE_H
#include <vector>
#include<math.h>
#include <unordered_map>
#include <cstdint>  // Include this for uint64_t
#include "types.h"
class Cache_line {
public:
    bool valid;
    bool dirty;
    Addr tag;
    uint64_t last_access_time;
    int frequency;
    int core_id;
    Cache_line():valid(false), dirty(false), tag(0), last_access_time(0), frequency(0), core_id(0) {}


};
class Cache_set {
public:
    Cache_line* line;
    Cache_set(int ways):line(new Cache_line[ways]) {}
    ~Cache_set() {
        delete[] line;
    }



};



class Cache {
public:
    Cache(int size, int associativity, int lineSize);
    
    void printStats(); 
    void printCache(); 
    int cache_lookup(Addr address,int write); 
    void cache_insert(Addr address);
    void cache_remove_lru(Addr address);
    void updateLRU();
    // Function to read data from the cache
    bool readData(Addr address, int& data) const;

    // Function to write data to the cache
    void writeData(Addr address, int data);

private:
    int size;            // Cache size in bytes
    int associativity;   // Cache associativity
    int lineSize;       // Cache block size
    int linesPerSet;         // Number of sets in the cache
    int lookups;
    int tag_bits;
    int index_bits;
    int offset_bits;
    int hits;

    std::vector<Cache_set*> sets;
    
    // Other necessary members and functions for cache implementation
};


#endif  // CACHE_H
