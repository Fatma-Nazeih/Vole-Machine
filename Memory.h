#ifndef MEMORY_H
#define MEMORY_H

#include <bits/stdc++.h>
using namespace std;

class Memory {
    vector<string> memory;
public:
    Memory();
    void set_memory(int address, const string &value);
    string get_memory(int address) const;
    void display() const;
    static bool is_hexa(const string &str);
};

#endif // MEMORY_H
