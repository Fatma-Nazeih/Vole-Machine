#include "Memory.h"
#include <bits/stdc++.h>
using namespace std;

class Memory {
    string memory[256];

public:
    Memory() {
        for (int i = 0; i < 256; i++) {
            memory[i] = "00";
        }
    }
    string get_memory(int address) {
        if (address >= 0 && address < 256) {
            return memory[address];
        }
        cout << "Error: Memory address out of range (0-255): " << address << endl;
        return "00";
    }
    void set_memory(int address, const string &value) {
        if (address >= 0 && address < 256) {
            memory[address] = value;
        } else {
            cout << "Error: Invalid memory address or value." << endl;
        }
    }
    void display() const {
        cout << "Main Memory:" << endl;
        cout << "   ";
        for (int i = 0; i < 16; i++) {
            cout << hex << uppercase << i << "  ";
        }
        cout << endl;
        for (int i = 0; i < 16; i++) {
            cout << hex << uppercase << i << "  ";
            for (int j = 0; j < 16; j++) {
                cout << setw(2) << setfill('0') << memory[i * 16 + j] << " ";
            }
            cout << endl;
        }
    }
    static bool is_hexa(const string &str) {
        for (char c : str) {
            if (!((c >= '0' && c <= '9') || (toupper(c) >= 'A' && toupper(c) <= 'F'))) {
                return false;
            }
        }
        return true;
    }
};
