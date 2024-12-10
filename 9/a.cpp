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
#include <map>
#include <tuple>

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



int main() {
    ifstream InputFile("./input.txt");
    // ifstream InputFile("./test.txt");

    string cursor;

    const int empty = -1;
    vector<int> seq; 
    while (getline(InputFile, cursor)) {
        std::vector<char> row(cursor.begin(), cursor.end());
        int i = 0;
        // cout << "=====" << endl;
        for (char c : row) {
            int num = c - '0';
            cout << num;
            if (i % 2 == 0) {
                int id = i / 2;
                for (int j = 0; j < num; j++) {
                    seq.push_back(id);
                }
            } else {
                for (int j = 0; j < num; j++) {
                    seq.push_back(empty);
                }
            }
            i += 1;
        }
        // cout << "=====" << endl;
    }

    // for (int a : seq) {
    //     if (a != empty) {
    //         cout << to_string(a);
    //     } else {
    //         cout << ".";
    //     }
    // }
    // cout << endl;

    while (true) {
        int s = seq.size();
        int replaceIndex = -1;
        for (int i = 0; i < s; i++) {
            if (seq[i] == empty) {
                replaceIndex = i;
                break;
            }
        }

        int tailIndex = -1;
        for (int i = s - 1; i >= 0; i--) {
            if (seq[i] != empty) {
                tailIndex = i;
                break;
            }
        }

        // cout << replaceIndex << " " << tailIndex << endl;
        if (replaceIndex < tailIndex) {
            seq[replaceIndex] = seq[tailIndex];
            seq[tailIndex] = empty;
        } else {
            break;
        }
    }

    long long checksum = 0;
    int i = 0;
    // cout << "-----" << endl;
    while (true) {
        int n = seq[i];
        if (n == empty) {
            break;
        }

        // cout << n;

        checksum += i * n;

        i += 1;
    }
    // cout << endl;
    // cout << "------" << endl;
    cout << endl;
    cout << checksum << endl;
    
    return 0;
}

