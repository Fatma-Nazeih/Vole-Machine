#include "Register.h"
#include <Bits/stdc++.h>
using namespace std;

class Register {
    string registers[16];

public:
    Register() {
        for (int i = 0; i < 16; i++) {
            registers[i] = "00";
        }
    }
    string get_register(int address) {
        if (address >= 0 && address < 16) {
            return registers[address];
        }
        cout << "Error: Register address out of range (0-15): " << address << endl;
        return "00";
    }
    void set_register(int address, const string &value) {
        if (address >= 0 && address < 16) {
            registers[address] = value;
        } else {
            cout << "Error: Invalid register address or value." << endl;
        }
    }
    void display() const {
        for (int i = 0; i < 16; ++i) {
            cout << i << ":" << registers[i] << endl;
        }
    }
};
