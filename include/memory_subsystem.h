#ifndef MEMORY_SUBSYSTEM_H
#define MEMORY_SUBSYSTEM_H

#include <cstdint>
#include "main_memory.h"
#include "cache.h"

class MemorySubsystem {
private:
    MainMemory memory;
    Cache cache;
    bool is_cache_enabled;
    int num_cycles;
    int penalty;
    bool load_miss;
    bool store_miss;

public:
    MemorySubsystem();
    int load_word(int address);
    int store_word(int address, int value);
    void enable_cache();
    void disable_cache();
    void print_memory(int address, int count);
    void print_cache();
    void print_cycle_count();
    void reset();
};

#endif
