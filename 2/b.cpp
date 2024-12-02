#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

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

bool isSafe(vector<int> level) {
    int last = level[0];
    int nx = level[1];

    int inc = 1;
    if (last > nx) {
        inc = -1;
    }
    
    for (int i = 1; i < level.size(); i++) {
        int cur = level[i];

        if (inc == 1 && cur < last) {
            return false;
        }
        if (inc == -1 && cur > last) {
            return false;
        }


        int diff = abs(cur - last);
        if (diff < 1 || diff > 3) {
            return false;
        }
        last = level[i];
    }
    return true;
}

int main() {
    ifstream InputFile("./input.txt");

    string cursor;

    vector< vector<int> > levels;

    while (getline(InputFile, cursor)) {
        vector<string> lineSplit = split(cursor, delimiter);
        vector<int> level;
        for (string num : lineSplit) {
            level.push_back(stoi(num));
        }
        levels.push_back(level);
    }

    int safe = 0;
    for (vector<int> level : levels) {

        bool add = true;
        bool badLevelTolerance = false;

        if (!isSafe(level)) {
            bool _isSafe = false;
            for (int i = 0; i < level.size(); i++) {
                vector<int> levelCopy(level);
                levelCopy.erase(levelCopy.begin() + i);
                if (isSafe(levelCopy)) {
                    _isSafe = true;
                }
            }
            if (!_isSafe) {
                add = false; 
            }
        }

        if (add) {
            safe += 1;
        }
    }
    cout << safe;

    return 0;
}

