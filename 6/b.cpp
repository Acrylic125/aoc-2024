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

struct Pos {
    int x, y;
};

Pos rotate90(int dx, int dy) {
    Pos result;
    if (dx == 0 && dy == -1) {
        result.x = 1;
        result.y = 0;
    } else if (dx == 1 && dy == 0) {
        result.x = 0;
        result.y = 1;
    } else if (dx == 0 && dy == 1) {
        result.x = -1;
        result.y = 0;
    } else if (dx == -1 && dy == 0) {
        result.x = 0;
        result.y = -1;
    }
    return result;
}

bool hasEnd(int _dy, int _dx, int sx, int sy, vector<vector<char>> map) {
    int rows = map.size();
    int cols = map[0].size();

    int x = sx;
    int y = sy;

    set<tuple<int, int, int, int>> dirPosBounded;
    int dx = _dx;
    int dy = _dy;

    while (true) {
        int nx = x + dx;
        int ny = y + dy;
        
        if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) {
            return true;
            // break;
        }

        char nc = map[ny][nx];
        if (nc == '#') {
            tuple<int, int, int, int> serializedDirPos = make_tuple(dx, dy, x, y);
            if (dirPosBounded.count(serializedDirPos) > 0) {
                return false;
            }
            dirPosBounded.insert(serializedDirPos);

            Pos next = rotate90(dx, dy);
            dx = next.x;
            dy = next.y;
        }

        x = x + dx;
        y = y + dy;
    }
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
    int startX = x;
    int startY = y;
    cout << x << ", " << y << endl;

    // set<string> candidates;
    set< tuple<int, int>> candidates;
    int steps = 1;
    while (true) {
        int nx = x + dx;
        int ny = y + dy;
        
        if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) {
            break;
        }

        char nc = map[ny][nx];
        if (nc == '#') {
            Pos next = rotate90(dx, dy);
            dx = next.x;
            dy = next.y;
        }
        x = x + dx;
        y = y + dy;
        
        if (!(x < 0 || x >= cols || y < 0 || y >= rows)) {
            char cur = map[y][x];
            if (cur == '.') {
                tuple<int, int> tup = make_tuple(x, y);
                candidates.insert(tup);
                // candidates.insert(to_string(x) + "," + to_string(y));
            }
        }
    }

    int count = 0;
    for (tuple<int, int> candidate : candidates) {
        // vector<string> s = split(candidate, ",");
        // int sx = stoi(s[0]);
        // int sy = stoi(s[1]);
        int sx = get<0>(candidate); 
        int sy = get<1>(candidate); 
        if (map[sy][sx] != '.') {
            cout << "Invalid!" << endl;
        }
        map[sy][sx] = '#';
        bool ended = hasEnd(0, -1, startX, startY, map);
        if (!ended) {
            count += 1;
        }
        map[sy][sx] = '.';
    }
    
    cout << count << endl;

    return 0;
}

