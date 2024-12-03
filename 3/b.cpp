#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <iostream>

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

string delimiter = " ";

int main() {
    ifstream InputFile("./input.txt");
    // ifstream InputFile("./test.txt");

    string cursor;

    //std::regex pattern(R"((mul\(\d+,\d+\))+)");
    std::regex pattern(R"(mul\(\d+,\d+\))"); 
    //std::regex pattern(R"(mul(\d+,\d+))");
    // regex pattern(R"(mul\((\d+),(\d+)\))");

    vector<string> instructions;
    while (getline(InputFile, cursor)) {
        instructions.push_back(cursor);
    }


    vector<string> mulInstructions;
    for (string instruction : instructions) {

        // Create an iterator to find all matches
        string input = instruction;
        auto matches_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
        auto matches_end = std::sregex_iterator();
        //
        // std::cout << "Matches found:" << std::endl;
        // for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
        //     std::smatch match = *i;
        //     string element = match.str();
        //     std::cout << element << std::endl;
        //     mulInstructions.push_back(element);
        // }

        auto it = std::sregex_iterator(instruction.begin(), instruction.end(), pattern);
        auto end = std::sregex_iterator();
        for(; it != end; ++it) {
            auto match = *it;
            auto element = match.str();
            // auto element = match[1].str();
            cout << element << " <<<< " << endl;
            mulInstructions.push_back(element);
        }
    }

    int sum = 0;
    for (string instruction : mulInstructions) {
        instruction.erase(0,4);
        instruction.erase(instruction.length() - 1);
        // cout << instruction;
        cout << instruction << " <-- " << endl;

        vector<string> splitInstruction = split(instruction, ",");
        int product = 1;
        for (string numStr : splitInstruction) {
            product *= stoi(numStr);
            cout << instruction << " | " << numStr << endl;
            //cout << numStr;
        }
        sum += product;
    }
    cout << sum;

    return 0;
}

