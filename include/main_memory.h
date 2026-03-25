#ifndef MAIN_MEMORY_H
#define MAIN_MEMORY_H

#include <vector>
#include <cstdint>

using namespace std;

class MainMemory {
private:
    vector<int> words;
    int num_cycles;
    int words_per_block;

public:
    MainMemory();
    int load_word(int address);
    void store_word(int address, int value);
    vector<int> read_block(int address);
    void reset();
};

#endif
