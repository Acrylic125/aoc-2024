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

    vector< vector<char> > map;
    while (getline(InputFile, cursor)) {
        std::vector<char> row(cursor.begin(), cursor.end());
        map.push_back(row);
    }

    int rows = map.size();
    int cols = map[0].size();

    vector<vector<int>> antinodesMap(rows, std::vector<int>(cols, 0));
    
    std::map<char, std::vector<std::tuple<int, int>>> atenas;
    
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            char c = map[y][x];
            if (c != '.') {
                std::vector<std::tuple<int, int>> locs;
                if (atenas.count(c) > 0) {
                    locs = atenas[c];
                }
                locs.push_back(make_tuple(x, y));
                atenas[c] = locs;
            }
        }
    }
    
    for (const auto& [frequency, locs] : atenas) {
        for (auto fromLoc : locs) {
            int fromX = get<0>(fromLoc);
            int fromY = get<1>(fromLoc);

            for (auto toLoc : locs) {
                int toX = get<0>(toLoc);
                int toY = get<1>(toLoc);

                if (fromX == toX && fromY == toY) {
                    continue;
                }

                int dx = toX - fromX;
                int dy = toY - fromY;

                int inc = 0;
                while (true) {
                    int nx = fromX + dx * inc;
                    int ny = fromY + dy * inc;

                    if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) {
                        break;
                    }

                    antinodesMap[ny][nx] += 1;
                    inc += 1;
                }

                inc = 0;
                while (true) {
                    int nx = fromX + dx * -inc;
                    int ny = fromY + dy * -inc;

                    if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) {
                        break;
                    }

                    antinodesMap[ny][nx] += 1;
                    inc += 1;
                }
            }
        }
    }

    int sum = 0;
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            int antinodes = antinodesMap[y][x];
            if (antinodes > 0) {
                sum += 1;
            }
        }
    }
    cout << sum << endl;
        
    return 0;
}

