#include <bits/stdc++.h>
using namespace std;

class Instructions
{
private:
int program_counter = 0;
public:
    void B_jump(string inst) {
        char R = inst[1];
        string address = inst.substr(2, 2);

        int r = stoi(string(1, R), nullptr, 16);
        int mem_address = stoi(address, nullptr, 16);

        if (registers[r] == registers[0]) {
            program_counter = mem_address;
            cout << "Jumped to address: " << hex << mem_address << endl;
        } else {
            cout << "No jump" << endl;
        }
    }
};

class memory
{
private:
    string arr[265];
public:
    memory()
    {
        for(int i = 0; i < 265; i++)
        {
            arr[i] = "00";
        }
    }

    string get(int ad)
    {
        if(ad >= 0 && ad < 265)
        {
            return arr[ad];
        }
        return ""; 
    }

    void set(int ad, string value)
    {
        if(ad >= 0 && ad < 265)
        {
            arr[ad] = value;
        }
    }

    ~memory()
    {
        for(int i = 0; i < 265; i++)
        {
            arr[i] = "00";
        }
    }
};

class Register
{
private:
    string arr[16];
public:
    Register()
    {
        for(int i = 0; i < 16; i++)
        {
            arr[i] = "00";
        }
    }

    string get(int ad)
    {
        if(ad >= 0 && ad < 265)
        {
            return arr[ad];
        }
        return ""; 
    }

    void set(int ad, string value)
    {
        if(ad >= 0 && ad < 265)
        {
            arr[ad] = value;
        }
    }

    ~Register()
    {
        for(int i = 0; i < 265; i++)
        {
            arr[i] = "00";
        }
    }
};

class machine 
{
private:
    int pc = 0;
    string ir;
    string arr[16];
    
public:

};

int main()
{
    cout << " hello" << endl;
    return 0;
}
