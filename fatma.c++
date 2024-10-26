#include <bits/stdc++.h>
using namespace std;

class Instructions
{

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
