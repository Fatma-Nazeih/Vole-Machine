#include "ALU.h"
#include <bits/stdc++.h>
#include "Register.h"
#include "Memory.h"
using namespace std;

class ALU {
    Memory &memory;
    Register &regist;

public:
    ALU(Memory &mem, Register &reg) : memory(mem), regist(reg) {}

    static string decimalToHex(int decimal) {
        if (decimal == 0) {
            return "00";
        }
        string hex;
        while (decimal > 0) {
            int remainder = decimal % 16;
            if (remainder < 10) {
                hex += (remainder + '0');
            } else {
                hex += (remainder - 10 + 'A');
            }
            decimal /= 16;
        }
        reverse(hex.begin(), hex.end());
        while (hex.length() < 2) {
            hex = "0" + hex;
        }
        return hex;
    }

    static int hexToDecimal(const string &hexStr) {
        return stoi(hexStr, nullptr, 16);
    }

    void add_unsigned_to_hex(char R, char S, char T) {
        int r = stoi(string(1, R), nullptr, 16);
        int s = stoi(string(1, S), nullptr, 16);
        int t = stoi(string(1, T), nullptr, 16);

        int registerS = stoi(regist.get_register(s), nullptr, 16);
        int registerT = stoi(regist.get_register(t), nullptr, 16);

        int result = registerS + registerT;

        stringstream ss;
        ss << hex << (result & 0xFF);
        regist.set_register(r, ss.str());
    }

    float decodeFloatingPoint(const string &hexStr) {
        if (hexStr.length() != 2 || !Memory::is_hexa(hexStr)) {
            cout << "Error: Invalid floating-point format for decoding to hexadecimal." << endl;
            return 0.0;
        }

        int hexValue = hexToDecimal(hexStr);

        string binaryStr = "";
        for (int i = 0; i < 8; ++i) {
            binaryStr = to_string(hexValue % 2) + binaryStr;
            hexValue /= 2;
        }

        int sign = (binaryStr[0] == '1') ? 1 : 0;
        int exponent = stoi(binaryStr.substr(1, 3), nullptr, 2);
        int mantissa = stoi(binaryStr.substr(4, 4), nullptr, 2);

        exponent -= 4;

        return pow(-1, sign) * (mantissa / 16.0) * pow(2, exponent);
    }

    string encodeFloatingPoint(float value) {
        int signBit = (value < 0) ? 1 : 0;
        value = fabs(value);

        int exponent = 0;
        while (value >= 1.0) {
            value /= 2.0;
            exponent++;
        }
        while (value < 0.5 && exponent > -4) {
            value *= 2.0;
            exponent--;
        }
        exponent += 4;

        int mantissa = int(value * 16);
        int hexValue = signBit * 128 + exponent * 16 + mantissa;

        return decimalToHex(hexValue);
    }
};
