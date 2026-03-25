#include "main_memory.h"
#include <iostream>

using namespace std;

MainMemory::MainMemory() {
    num_cycles = 100;
    words_per_block = 4;
    words.resize(1024);

    for (int i = 0; i < 1024; i++) {
        words[i] = 0;
    }
}

int MainMemory::load_word(int address) {
    if (address >= words.size()) {
        cout << "Memory load error: address out of bounds" << endl;
        return 0;
    }

    return words[address];
}

void MainMemory::store_word(int address, int value) {
    if (address >= words.size()) {
        cout << "Memory store error: address out of bounds" << endl;
        return;
    }

    words[address] = value;
}

vector<int> MainMemory::read_block(int address) {
    vector<int> block;

    for (int i = 0; i < words_per_block; i++) {
        if (address + i >= words.size()) {
            break;
        }

        block.push_back(words[address + i]);
    }

    return block;
}

void MainMemory::reset() {
    for (int i = 0; i < words.size(); i++) {
        words[i] = 0;
    }
}
