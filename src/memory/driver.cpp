#include "driver.h"
#include "memory_subsystem.h"

#include <iostream>
#include <string>

using namespace std;

void Driver::run() {
    MemorySubsystem memory;

    string command;

    cout << "Driver Commands" << endl;
    cout << "  lw <address>" << endl;
    cout << "  sw <address> <value>" << endl;
    cout << "  cache on" << endl;
    cout << "  cache off" << endl;
    cout << "  print cache" << endl;
    cout << "  print memory <address> <count>" << endl;
    cout << "  cycle" << endl;
    cout << "  reset" << endl;
    cout << "  quit" << endl;

    while (true) {
        cout << endl << "> ";
        cin >> command;

        if (command == "lw") {
            int address;
            cin >> address;
            memory.load_word(address);
        }
        else if (command == "sw") {
            int address;
            int value;
            cin >> address >> value;
            memory.store_word(address, value);
        }
        else if (command == "cache") {
            string s;
            cin >> s;

            if (s == "on") {
                memory.enable_cache();
            }
            else if (s == "off") {
                memory.disable_cache();
            }
            else {
                cout << "Invalid command" << endl;
            }
        }
        else if (command == "print") {
            string s;
            cin >> s;

            if (s == "cache") {
                memory.print_cache();
            }
            else if (s == "memory") {
                int start;
                int count;
                cin >> start >> count;
                memory.print_memory(start, count);
            }
            else {
                cout << "Invalid command" << endl;
            }
        }
        else if (command == "cycle") {
            memory.print_cycle_count();
        }
        else if (command == "reset") {
            memory.reset();
            cout << "Memory subsystem reset" << endl;
        }
        else if (command == "quit") {
            cout << "Exiting driver" << endl;
            break;
        }
        else {
            cout << "Unknown command" << endl;
        }
    }
}
