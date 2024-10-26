#include "bits/stdc++.h"
using namespace std;

class instructions {
private:
    char opcode;
    string  R;
    string R2;
    string add_mem;
    string loaded_imm_value;
    int registers[16] = {0};
    int memory[256] = {0};

public:
    void parse(string inst){
        if (inst.length() < 4) {
            cout << "error: instruction is too short: " << inst << endl;
            return;
        }

        inst = inst.substr(0, 4);

        for (char c : inst) {
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) {
                cout << "error: invalid character in instruction: " << inst << endl;
                return;
            }
        }

        R = inst[1];
        add_mem = inst.substr(inst.length() - 2);
        loaded_imm_value = inst.substr(inst.length() - 2);
        if (inst[0] == '1'){
            load(R , add_mem);

        }
        if (inst[0] == '2'){
            load_imm ( R , loaded_imm_value);
        }
        if (inst[0] == '3'){
            store(R,add_mem);
        }
        if (inst[0] == '4'){
            R2 = inst[3];
            move(R , R2);
        }
        if (inst[0] == '5'){
            opcode = 5;
        }
        if (inst[0] == '6'){
            opcode = 6;
        }
        if (inst[0] == 'A'){
            opcode = 'A';
        }
        if (inst[0] == 'B'){
            opcode = 'B';
        }
        else{
            cout << "Invalid opcode: " << inst[0] << endl;
            return;
        }

    }
    void load (string R , string add_mem){
        int r = stoi(R, 0, 16);
        int mem = stoi(add_mem, 0, 16);
        registers[r] = memory[mem];
    };
    void load_imm (string R , string loaded_imm_value){
        int r = stoi(R, 0, 16);
        int value = stoi(loaded_imm_value, 0, 16);
        registers[r] = value;

    };void store (string R , string add_mem){
        int r = stoi(R, 0, 16);
        int mem = stoi(add_mem, 0, 16);
        memory[mem] = registers[r];
    };void move (string R , string R2){
        int r = stoi(R, 0, 16);
        int r2 = stoi(R2, 0, 16);
        registers[r2] = registers[r];

    };void add_1 (char opcode , char R , char x , char y){

    };void add_2 (char opcode , char R , char x , char y){

    };void B_jump (char opcode , char R , char x , char y){

    };void C_Halt (char opcode , char R , char x , char y){

    };
};

