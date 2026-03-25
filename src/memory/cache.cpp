#include "cache.h"

using namespace std;

Cache::Cache(MainMemory* memory) {
    this->memory = memory;
    num_sets = 4;

    sets.resize(num_sets);

    for (int i = 0; i < num_sets; i++) {
        sets[i].line0.valid = false;
        sets[i].line0.tag = 0;
        sets[i].line0.lru = 0;
        sets[i].line0.data.resize(4);

        sets[i].line1.valid = false;
        sets[i].line1.tag = 0;
        sets[i].line1.lru = 0;
        sets[i].line1.data.resize(4);

        for (int j = 0; j < 4; j++) {
            sets[i].line0.data[j] = 0;
            sets[i].line1.data[j] = 0;
        }
    }

    num_hits = 0;
    num_misses = 0;
    penalty = 3;
    remaining_cycles = 0;
    load_miss = false;
    store_miss = false;
}

int Cache::load_word(int address, int &cycles) {
    int block_offset = address % 4;
    int block_number = address / 4;

    int set_index = block_number % num_sets;
    int tag = block_number / num_sets;

    CacheSet &set = sets[set_index];

    if (set.line0.valid && set.line0.tag == tag) {
        num_hits++;
        cycles = 1;
        set.line0.lru = 1;
        set.line1.lru = 0;
        return set.line0.data[block_offset];
    }

    if (set.line1.valid && set.line1.tag == tag) {
        num_hits++;
        cycles = 1;
        set.line1.lru = 1;
        set.line0.lru = 0;
        return set.line1.data[block_offset];
    }

    if (remaining_cycles == 0 && !load_miss) {
        num_misses++;
        cycles = penalty + 1;
        remaining_cycles = penalty;
        load_miss = true;
    }

    if (remaining_cycles == 0) {
        vector<int> block = memory->read_block(block_number * 4);

        CacheLine *replace_line;

        if (!set.line0.valid) {
            replace_line = &set.line0;
        } else if (!set.line1.valid) {
            replace_line = &set.line1;
        } else if (set.line0.lru == 0) {
            replace_line = &set.line0;
        } else {
            replace_line = &set.line1;
        }

        for (int i = 0; i < 4; i++) {
            replace_line->data[i] = block[i];
	}

	replace_line->valid = true;
	replace_line->tag = tag;

	if (replace_line == &set.line0) {
            set.line0.lru = 1;
	    set.line1.lru = 0;
	} else {
	    set.line1.lru = 1;
	    set.line0.lru = 0;
	}

        load_miss = false;

	return replace_line->data[block_offset];
    } else {
        remaining_cycles--;
        return -1;
    }
}

int Cache::store_word(int address, int value, int &cycles) {
    int block_offset = address % 4;
    int block_number = address / 4;

    int set_index = block_number % num_sets;
    int tag = block_number / num_sets;

    cycles = penalty + 1;

    CacheSet &set = sets[set_index];

    if (set.line0.valid && set.line0.tag == tag && remaining_cycles == 0) {
        num_hits++;
        set.line0.data[block_offset] = value;
        set.line0.lru = 1;
        set.line1.lru = 0;
    } else if (set.line1.valid && set.line1.tag == tag && remaining_cycles == 0) {
        num_hits++;
        set.line1.data[block_offset] = value;
        set.line1.lru = 1;
        set.line0.lru = 0;
    }

    if (remaining_cycles == 0 && !store_miss) {
        num_misses++;
        cycles = penalty + 1;
        remaining_cycles = penalty;
        store_miss = true;
    }

    if (remaining_cycles == 0) {
        memory->store_word(address, value);
        store_miss = false;
        return 0;
    } else {
        remaining_cycles--;
        return -1;
    } 
}

void Cache::print_cache() {
    cout << "Cache Contents" << endl;

    for (int i = 0; i < num_sets; i++) {
        cout << "Set " << i << endl;

        cout << "  Line 0: ";
        cout << "Valid=" << sets[i].line0.valid << " Tag=" << sets[i].line0.tag << " LRU=" << sets[i].line0.lru << " Data=";
        for (int j = 0; j < 4; j++) {
            cout << sets[i].line0.data[j] << " ";
        }
        cout << endl;

        cout << "  Line 1: ";
        cout << "Valid=" << sets[i].line1.valid << " Tag=" << sets[i].line1.tag << " LRU=" << sets[i].line1.lru << " Data=";
        for (int j = 0; j < 4; j++) {
            cout << sets[i].line1.data[j] << " ";
        }
        cout << endl;
    }
}

void Cache::print_hit_miss() {
    cout << "Cache Hits: " << num_hits << endl;
    cout << "Cache Misses: " << num_misses << endl;
}

void Cache::reset_cache() {
    for (int i = 0; i < num_sets; i++) {
        sets[i].line0.valid = false;
        sets[i].line0.tag = 0;
        sets[i].line0.lru = 0;

        sets[i].line1.valid = false;
        sets[i].line1.tag = 0;
        sets[i].line1.lru = 0;

        for (int j = 0; j < 4; j++) {
            sets[i].line0.data[j] = 0;
            sets[i].line1.data[j] = 0;
        }
    }

    num_hits = 0;
    num_misses = 0;
}
