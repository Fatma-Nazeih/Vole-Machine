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
    Machine(Memory &mem, Register &reg) : memory(mem), regist(reg), pc(0), alu(mem, reg) {}

    void load_instructions(vector<string> &program, int start_address) {
        invalid_instructions.clear();
        pc = start_address;

        for (string &inst : program) {
            if (inst.length() != 4 || !Memory::is_hexa(inst)) {
                invalid_instructions.push_back(inst);
            } else {
                memory.set_memory(start_address++, inst.substr(0, 2));
                memory.set_memory(start_address++, inst.substr(2, 2));
            }
        }
    }

    string fetch() {
        if (pc < 256) {
            string instruction = memory.get_memory(pc) + memory.get_memory(pc + 1);
            pc += 2;
            return instruction;
        }
        return "";
    }

    void decode(const string &instruction, string &opcode, string &operand1, string &operand2) {
        opcode = instruction.substr(0, 1);
        operand1 = instruction.substr(1, 1);
        operand2 = instruction.substr(2, 2);
    }

    void execute(const string &opcode, const string &operand1, const string &operand2) {
         try {
            if (opcode == "1") {
                int R = alu.hexToDecimal(operand1);
                int XY = alu.hexToDecimal(operand2);
                if (R < 0 || R >= 16) {
                    cout << "Error: Register index out of range." << endl;
                    return;
                }
                regist.set_register(R, memory.get_memory(XY));
            } else if (opcode == "2") {
                int R = alu.hexToDecimal(operand1);
                if (R < 0 || R >= 16) {
                    cout << "Error: Register index out of range." << endl;
                    return;
                }
                regist.set_register(R, operand2);
            } else if (opcode == "3") {
                int R = alu.hexToDecimal(operand1);
                if (R < 0 || R >= 16) {
                    cout << "Error: Register index out of range." << endl;
                    return;
                }
                int XY = alu.hexToDecimal(operand2);
                if (XY < 0 || XY >= 256) {
                    cout << "Error: Memory address out of range (0-255)." << endl;
                    return;
                }
                memory.set_memory(XY, regist.get_register(R));
                if (operand2 == "00") {
                    string value = regist.get_register(R);
                    memory_values.push_back(value);
                    cout << "Memory 00 : " << value << endl;
                }
            } else if (opcode == "4") {
                int R = alu.hexToDecimal(operand2.substr(0, 1));
                int S = alu.hexToDecimal(operand2.substr(1, 1));
                if (R < 0 || R >= 16) {
                    cout << "Error: Register index out of range." << endl;
                    return;
                }
                regist.set_register(S, regist.get_register(R));
            } else if (opcode == "5") {
                int R = alu.hexToDecimal(operand1);
                int S = alu.hexToDecimal(operand2.substr(0, 1));
                int T = alu.hexToDecimal(operand2.substr(1, 1));

                if (R < 0 || R >= 16 || S < 0 || S >= 16 || T < 0 || T >= 16) {
                    cout << "Error: Register index out of range." << endl;
                    return;
                }

                int registerS = (alu.hexToDecimal(regist.get_register(S)));
                int registerT = (alu.hexToDecimal(regist.get_register(T)));

                int result = registerS + registerT;

                stringstream ss;
                ss << hex << uppercase << setw(2) << setfill('0') << (result & 0xFF);
                regist.set_register(R, ss.str());

            } else if (opcode == "6") {
                int R1 = alu.hexToDecimal(operand1);
                int R2 = alu.hexToDecimal(operand2.substr(0, 1));
                int R3 = alu.hexToDecimal(operand2.substr(1, 1));
                if (R1 < 0 || R1 >= 16 || R2 < 0 || R2 >= 16 || R3 < 0 || R3 >= 16) {
                    cout << "Error: Register index out of range." << endl;
                    return;
                }

                float val1 = alu.decodeFloatingPoint(regist.get_register(R2));
                float val2 = alu.decodeFloatingPoint(regist.get_register(R3));

                float result = val1 + val2;

                string resultHex = alu.encodeFloatingPoint(result);
                regist.set_register(R1, resultHex);
            } else if (opcode == "B" || opcode == "b") {
                int R = alu.hexToDecimal(operand1);
                int address = alu.hexToDecimal(operand2);
                if (regist.get_register(R) == regist.get_register(0)) {
                    pc = address;
                }
            } else if (opcode == "C" || opcode == "c") {
                cout << "Halt instruction." << endl;
                pc = 256;
            }
        } catch (const std::invalid_argument &e) {
            cout << "Error: Invalid argument for stoi conversion." << endl;
        } catch (const std::out_of_range &e) {
            cout << "Error: Out of range argument for stoi conversion." << endl;
        }
    }

    void run_whole() {
        while (pc < 256) {
            string instruction = fetch();
            if (instruction.empty()) break;
            string opcode, operand1, operand2;
            decode(instruction, opcode, operand1, operand2);
            execute(opcode, operand1, operand2);
        }
        cout << "Final state of Registers:" << endl;
        regist.display();
        cout << "Final state of Memory:" << endl;
        memory.display();
    }

     void display_invalid_instructions() {
        if (!invalid_instructions.empty()) {
            cout << "Invalid Instructions:" << endl;
            for (const string &inst : invalid_instructions) {
                cout << "Instruction: " << inst << endl;
            }
        }
    }

    void run_step_by_step() {
        while (pc < 256) {
            string instruction = fetch();
            if (instruction.empty()) break;
            string opcode, operand1, operand2;
            decode(instruction, opcode, operand1, operand2);
            execute(opcode, operand1, operand2);
        }
    }
};

#endif // MACHINE_H
