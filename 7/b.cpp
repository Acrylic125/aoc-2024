#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <set>

using namespace std;

std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    std::string temp = s; // Make a local copy to modify

    while ((pos = temp.find(delimiter)) != std::string::npos) {
        token = temp.substr(0, pos);
        tokens.push_back(token);
        temp.erase(0, pos + delimiter.length());
    }
    tokens.push_back(temp);

    return tokens;
}

void printMap(vector< vector<char>> map) {
    for (vector<char> row : map) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
}

struct Eqn {
    vector<long long> operands;
    long long result;
};

bool hasValidRes(Eqn eqn, int operandIndex, long long acc) {
    if (operandIndex >= eqn.operands.size() - 1) {
        return acc == eqn.result;
    }
    long long _acc = acc;
    if (operandIndex == 0) {
        _acc = eqn.operands[operandIndex];
    }
    long long multipliedAcc = _acc * eqn.operands[operandIndex + 1];
    long long addAcc = _acc + eqn.operands[operandIndex + 1];
    bool hasValidMul = hasValidRes(eqn, operandIndex + 1, multipliedAcc);
    if (hasValidMul) {
        return true;
    }
    bool hasValidAdd = hasValidRes(eqn, operandIndex + 1, addAcc);
    if (hasValidAdd) {
        return true;
    }
    return false;
}

int main() {
    ifstream InputFile("./input.txt");
    // ifstream InputFile("./test.txt");

    string cursor;

    vector<Eqn> eqns;
    cout << "T1 " << endl;
    while (getline(InputFile, cursor)) {
        vector<string> rs = split(cursor, ": ");
        long long result = stol(rs[0]);
        vector<string> soperands = split(rs[1], " ");
        vector<long long> operands;
        for (string operand : soperands) {
            operands.push_back(stoi(operand));
        }
        Eqn eqn;
        eqn.result = result;
        eqn.operands = operands;
        eqns.push_back(eqn);
    }
    cout << "T2 " << endl;

    long long sum = 0;
    for (Eqn eqn : eqns) {
        bool valid = hasValidRes(eqn, 0, 0);
        cout << eqn.result << " " << valid << endl;
        if (valid) {
            sum += eqn.result;
        }
    }
    cout << sum << endl;
        
    return 0;
}

