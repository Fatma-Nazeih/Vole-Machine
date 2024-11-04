#ifndef ALU_H
#define ALU_H

#include <bits/stdc++.h>
#include "Register.h"
#include "Memory.h"
using namespace std;

class ALU {
    Memory &memory;
    Register &regist;

public:
    ALU(Memory &mem, Register &reg);
    static string decimalToHex(int decimal);
    static int hexToDecimal(const string &hexStr);
    void add_unsigned_to_hex(char R, char S, char T);
    float decodeFloatingPoint(const string &hexStr);
    string encodeFloatingPoint(float value);
};

#endif // ALU_H
