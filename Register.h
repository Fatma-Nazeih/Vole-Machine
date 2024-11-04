#ifndef REGISTER_H
#define REGISTER_H

#include <bits/stdc++.h>
using namespace std;

class Register {
    vector<string> reg;
public:
    Register();
    void set_register(int index, const string &value);
    string get_register(int index) const;
    void display() const;
};

#endif // REGISTER_H
