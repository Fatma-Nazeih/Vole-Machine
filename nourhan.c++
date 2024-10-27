#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Memory {
    string memory[256];
public:
    Memory() {
        for (int i = 0; i < 256; i++){
            memory[i] = "00";
        }
    }
    string get_memory(int address) {
        if (address >= 0 && address < 256) {
            return memory[address];
        }
        return "00";
    }
    void set_memory(int address, const string &value) {
        if (address >= 0 && address < 256) {
            memory[address] = value;
        }
    }
    void display() const {
        for (int i = 0; i < 256; ++i){
            cout << i  << ":" << memory[i] << endl;
        }
    }
};

class Register {
    string registers[16];
public:
    Register() {
        for (int i = 0; i < 16; i++){
            registers[i] = "00";
        }
    }
    string get_register(int address) {
        if (address >= 0 && address < 16){
            return registers[address];
        }
        return "00";
    }
    void set_register(int address, const string &value) {
        if (address >= 0 && address < 16){
            registers[address] = value;
        }
    }
    void display() const {
        for (int i = 0; i < 16; ++i){
            cout << i  << ":" << registers[i] << endl;
        }
    }
};

class CPU {
    Memory &memory;
    Register &regist;
    int pc;
    vector<string> instructions;

public:
    CPU(Memory &mem, Register &reg) : memory(mem), regist(reg) {
        pc = 0;
    }


    void load_instructions(const vector<string> &program) {
        instructions = program;
        pc = 0;
    }

    string fetch() {
        if (pc < instructions.size()){
            return instructions[pc++];
        }
        return "";
    }

    void decode(const string &instruction, string &opcode, string &operand1, string &operand2) {
        opcode = instruction[0];
        operand1 = instruction[1];
        operand2 = instruction.substr(2);
    }

    void execute(const string &opcode, const string &operand1, const string &operand2) {
        if (opcode == "1"){
            int R = stoi(operand1);
            int XY = stoi(operand2);
            regist.set_register(R, memory.get_memory(XY));
        }
        if (opcode == "2"){
            int R = stoi(operand1);
            regist.set_register(R, operand2);
        }
        if (opcode == "3"){
            int R = stoi(operand1);
            int XY = stoi(operand2);
            memory.set_memory(XY, regist.get_register(R));
        }
        if (opcode == "4"){
            string R1 = operand2.substr(0,1);
            string S1 = operand2.substr(1,1);
            int R = stoi(R1);
            int S = stoi(S1);
            regist.set_register(S, regist.get_register(R));
        }
    }

    void run() {
        string opcode, operand1, operand2;
        while (true) {

            string instruction = fetch();
            if (instruction.empty()) {
                break;
            }
            decode(instruction, opcode, operand1, operand2);

            if (opcode == "C"){
                break;
            }
            execute(opcode, operand1, operand2);
        }
    }
};

int main() {
    Memory memory;
    Register reg;
    CPU cpu(memory, reg);

    while (true) {
        cout << "welcome to our vole machine" << endl;
        cout << "1. Load a program and run " << endl;
        cout << "2. Exit " << endl;
        cout << "option : ";
        char choice;
        cin >> choice;

        if (choice == '1') {
            cout << "Enter the program file name (filename.txt): ";
            string filename;
            cin >> filename;

            ifstream inputFile(filename);
            if (!inputFile) {
                cout << "Unable to open program file." << endl;
                continue;
            }

            vector<string> program;
            string instruction;
            while (inputFile >> instruction) {
                program.push_back(instruction);
            }
            inputFile.close();
            cpu.load_instructions(program);

            cout << "Program loaded successfully." << endl;
            cpu.run();

            cout << "Register values:" << endl;
            reg.display();
            cout << "Memory values:" << endl;
            memory.display();

            
        } else if (choice == '2') {
            cout << "Exiting the program." << endl;
            return 0;
        } else {
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
}


