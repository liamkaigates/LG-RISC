#include "memory_subsystem.h"
#include <iostream>

using namespace std;

MemorySubsystem::MemorySubsystem() : memory(), cache(&memory) {
    is_cache_enabled = true;
    num_cycles = 0;
    penalty = 3;
    load_miss = false;
    store_miss = false;
}

int MemorySubsystem::load_word(int address) {
    int cycles = 1;
    int value;

    if (is_cache_enabled) {
        value = cache.load_word(address, cycles);
    } else {
        value = memory.load_word(address);
        cycles = penalty + 1;
    }

    if (value == -1) {
        cout << "Wait" << endl;
        load_miss = true;
        return -1;
    }

    if (load_miss) {
        load_miss = false;
        cycles += penalty;
    }

    num_cycles += cycles;

    cout << "Load Address: " << address << endl;
    cout << "Value: " << value << endl;
    cout << "Cycles: " << cycles << endl;

    return value;
}

int MemorySubsystem::store_word(int address, int value) {
    int cycles = penalty + 1;
    int result = 0;

    if (is_cache_enabled) {
        result = cache.store_word(address, value, cycles);
    } else {
        memory.store_word(address, value);
    }

    if (result == -1) {
       cout << "Wait" << endl;
       return -1;
    }

    num_cycles += cycles;

    cout << "Store Address: " << address << endl;
    cout << "Stored Value: " << value << endl;
    cout << "Cycles: " << cycles << endl;

    return 0;
}

void MemorySubsystem::enable_cache() {
    is_cache_enabled = true;
    cout << "Cache enabled" << endl;
}

void MemorySubsystem::disable_cache() {
    is_cache_enabled = false;
    cout << "Cache disabled" << endl;
}

void MemorySubsystem::print_memory(int start, int count) {
    for (int i = 0; i < count; i++) {
        int address = start + i;
        cout << "MEM[" << address << "] = " << memory.load_word(address) << endl;
    }
}

void MemorySubsystem::print_cache() {
    cache.print_cache();
}

void MemorySubsystem::print_cycle_count() {
    cout << "Total Cycles: " << num_cycles << endl;
    cache.print_hit_miss();
}

void MemorySubsystem::reset() {
    memory.reset();
    cache.reset_cache();
    num_cycles = 0;
}
