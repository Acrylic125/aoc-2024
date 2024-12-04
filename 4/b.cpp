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

int XMAS_LENGTH = 4;

struct WordDirection {
    int dx, dy;

    WordDirection(int dx, int dy) : dx(dx), dy(dy) {} 
};

std::vector<WordDirection> directions{
    WordDirection(0, 1), 
    WordDirection(1, 1), 
    WordDirection(1, 0), 
    WordDirection(1, -1), 
    WordDirection(0, -1), 
    WordDirection(-1, -1), 
    WordDirection(-1, 0), 
    WordDirection(-1, 1), 
};
vector<char> word{
    'X', 'M', 'A', 'S'
};


vector<vector<vector<char>>> MAS_MATRICES{
    {
        { 'M', '.', 'S' },
        { '.', 'A', '.' },
        { 'M', '.', 'S' },
    },
    {
        { 'S', '.', 'M' },
        { '.', 'A', '.' },
        { 'S', '.', 'M' },
    },
    {
        { 'S', '.', 'S' },
        { '.', 'A', '.' },
        { 'M', '.', 'M' },
    },
    {
        { 'M', '.', 'M' },
        { '.', 'A', '.' },
        { 'S', '.', 'S' },
    },
};

int countXMAS(vector< vector<char> > &map, int row, int col, vector< vector<char> > &shadowMap) {
    int rows = map.size();
    int cols = map[0].size();

    if (map[row][col] != 'A') return 0;
    
    for (vector<vector<char>> matrix : MAS_MATRICES) {
        bool shouldCount = true;
        for (int _row = 0; _row < 3; _row++) {
            vector<char> matrixRow = matrix[_row];
            for (int _col = 0; _col < 3; _col++) {
                char c = matrixRow[_col];
                
                int mRow = row - 1 + _row;
                int mCol = col - 1 + _col;
                if (mRow < 0 || mRow >= rows || mCol < 0 || mCol >= cols) {
                    return 0;
                }
                if (c == '.') {
                    continue;
                }
                if (map[mRow][mCol] != c) {
                    shouldCount = false;
                    break;
                }
            }
        }
        if (shouldCount) {
            return 1;
        }
    }
    return 0;

    // for (WordDirection dir : directions) {
    //     bool shouldCount = true;
    //     for (int i = 0; i < word.size(); i++) {
    //         char c = word[i];
    //         int ox = (i - 1) * dir.dx + col;
    //         int oy = (i - 1) * dir.dy + row;
    //         if (ox < 0 || ox >= cols || oy < 0 || oy >= rows) {
    //             shouldCount = false;
    //             // cout << "Out of bounds" << endl;
    //             break;
    //         }
    //         if (map[oy][ox] != c) {
    //             shouldCount = false;
    //             // cout << "Wrong char, " << c << " got " << map[oy][ox] << endl;
    //             break;
    //         }
    //     }
    //     if (shouldCount) {
    //
    //         for (int i = 0; i < word.size(); i++) {
    //             int ox = (i - 1) * dir.dx + col;
    //             int oy = (i - 1) * dir.dy + row;
    //             shadowMap[oy][ox] = map[oy][ox];
    //         }
    //
    //         // cout << "Added" << endl;
    //         count += 1;
    //     }
    // }
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

    vector<vector<char>> shadowMap = vector<vector<char>>(rows, vector<char>(cols, '.'));

    cout << rows << " x " << cols << endl;

    printMap(map);

    int count = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // cout << row << " " << col << endl;
            int cnt = countXMAS(
                map, row, col, shadowMap
            );
            count += cnt;
        }
    }
    printMap(shadowMap);
    cout << count;

    return 0;
}

