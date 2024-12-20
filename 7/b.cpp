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

struct EqnVariant {
    vector<Eqn> variants;
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

void genVariants(Eqn base, vector<Eqn> &variants, int index, vector<long long> &acc) {
    if (index >= base.operands.size()) {
        Eqn eqn;
        eqn.result = base.result;
        eqn.operands = acc;
        variants.push_back(eqn);
        return;
    }
    if (index > 0) {
        vector<long long> _acc1(acc);
        _acc1.push_back(base.operands[index]);
        genVariants(base, variants, index + 1, _acc1);

        vector<long long> _acc2(acc);
        int li = _acc2.size() - 1;
        _acc2[li] = stol(to_string(_acc2[li]) + to_string(base.operands[index]));
        genVariants(base, variants, index + 1, _acc2);
    } else {
        vector<long long> _acc1(acc);
        _acc1.push_back(base.operands[index]);
        genVariants(base, variants, index + 1, _acc1);
    }
    
}

int main() {
    // ifstream InputFile("./input.txt");
    ifstream InputFile("./test.txt");

    string cursor;

    vector<vector<Eqn>> eqnVariants;
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

        vector<Eqn> variants;
        vector<long long> acc;
        genVariants(eqn, variants, 0, acc);

        cout << "---" << endl;
        for (Eqn eqn : variants) {
            for (long long i : eqn.operands)
                std::cout << i << ' ';
            cout << endl;
        }

        eqnVariants.push_back(variants);
        // eqns.push_back(eqn);
    }

    long long sum = 0;
    
    for (vector<Eqn> variants : eqnVariants) {
        bool valid = false;
        cout << variants.size() << endl;
        for (Eqn eqn : variants) {
            bool _valid = hasValidRes(eqn, 0, 0);
            cout << eqn.result << " " << valid << endl;
            if (_valid) {
                valid = true;
                break;
            }
        }
        if (valid) {
            sum += variants[0].result;
        }
    }
    cout << sum << endl;
    // for (Eqn eqn : eqns) {
    //     bool valid = hasValidRes(eqn, 0, 0);
    //     cout << eqn.result << " " << valid << endl;
    //     if (valid) {
    //         sum += eqn.result;
    //     }
    // }
    // cout << sum << endl;
        
    return 0;
}

