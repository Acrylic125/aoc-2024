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

string delimiter = "   ";

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
    // ifstream InputFile("./test_2.txt");

    string cursor;

    vector< vector<char> > map;
    while (getline(InputFile, cursor)) {
        std::vector<char> row(cursor.begin(), cursor.end());
        map.push_back(row);
    }
        
    set<string> explored;

    int dx = 0, dy = -1;
    int x, y;
    int rows = map.size();
    int cols = map[0].size();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (map[row][col] == '^') {
                x = col;
                y = row;
                break;
            }
        }
    }
    cout << x << ", " << y << endl;

    int steps = 1;
    explored.insert(to_string(x) + "," + to_string(y));
    while (true) {
        int nx = x + dx;
        int ny = y + dy;
        
        if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) {
            break;
        }

        char nc = map[ny][nx];
        if (nc == '#') {
            // 
            if (dx == 0 && dy == -1) {
                dx = 1;
                dy = 0;
            } else if (dx == 1 && dy == 0) {
                dx = 0;
                dy = 1;
            } else if (dx == 0 && dy == 1) {
                dx = -1;
                dy = 0;
            } else if (dx == -1 && dy == 0) {
                dx = 0;
                dy = -1;
            }
        }
        x = x + dx;
        y = y + dy;
        
        if (!(x < 0 || x >= cols || y < 0 || y >= rows)) {
            // cout << "TTT 1 : " << x << ", " << y << endl;
            char cur = map[y][x];
            // cout << "TTT 2" << endl;
            if (cur == '.' || cur == '^') {
                explored.insert(to_string(x) + "," + to_string(y));
            }
        }
    }
    
    cout << explored.size() << endl;

    return 0;
}

