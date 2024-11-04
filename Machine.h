#ifndef MACHINE_H
#define MACHINE_H

#include "ALU.h"
#include <bits/stdc++.h>
using namespace std;

class Machine {
    Memory &memory;
    Register &regist;
    int pc;
    vector<string> invalid_instructions;
    vector<string> memory_values;
    ALU alu;

public:
    Machine(Memory &mem, Register &reg);

    void load_instructions(vector<string> &program, int start_address);

    string fetch();

    void decode(const string &instruction, string &opcode, string &operand1, string &operand2);

    void execute(const string &opcode, const string &operand1, const string &operand2);

    void run_whole();
     
    void display_invalid_instructions();

    void run_step_by_step();
};

#endif // MACHINE_H
