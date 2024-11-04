#include <bits/stdc++.h>
#include "Machine.h"
#include "ALU.h"
#include "Memory.h"
#include "Register.h"
using namespace std;
int main() {
    Memory memory;
    Register reg;
    Machine vole_machine(memory, reg);

    cout << "Welcome to our Vole Machine" << endl;
    while (true) {
        cout << "1. Load the file" << endl;
        cout << "2. Exit" << endl;
        cout << "Option (1-2): ";
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

            cout << "Enter the starting memory location (in hex, e.g. 10 or 1C): ";
            string start_hex;
            cin >> start_hex;
            int start_address = stoi(start_hex, nullptr, 16);

            vole_machine.load_instructions(program, start_address);
            cout << "Program loaded successfully." << endl;
            vole_machine.display_invalid_instructions();

            cout << "1.1 Step by step execution" << endl;
            cout << "1.2 Execute all at once" << endl;
            cout << "Choose option (1.1 or 1.2): ";
            string execution_choice;
            cin >> execution_choice;

            if (execution_choice == "1.1") {
                vole_machine.run_step_by_step();
            } else if (execution_choice == "1.2") {
                vole_machine.run_whole();
            } else {
                cout << "Invalid execution choice." << endl;
            }

        } else if (choice == '2') {
            cout << "Exiting the program." << endl;
            return 0;
        } else {
            cout << "Invalid choice. Please enter a valid option." << endl;}
}
}
