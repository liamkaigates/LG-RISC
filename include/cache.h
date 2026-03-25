#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstdint>
#include <iostream>
#include "main_memory.h"

using namespace std;

struct CacheLine {
    bool valid;
    int tag;
    vector<int> data;
    int lru;
};

struct CacheSet {
    CacheLine line0;
    CacheLine line1;
};

class Cache {
private:
    MainMemory* memory;
    int num_sets;
    vector<CacheSet> sets;
    int num_hits;
    int num_misses;
    int penalty;
    int remaining_cycles;
    bool load_miss;
    bool store_miss;

public:
    Cache(MainMemory* memory);
    int load_word(int address, int &num_cycles);
    int store_word(int address, int value, int &num_cycles);
    void print_cache();
    void print_hit_miss();
    void reset_cache();
};

#endif
