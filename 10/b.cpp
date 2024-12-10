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

void printMap(vector< vector<int>> map) {
    for (vector<int> row : map) {
        for (int c : row) {
            cout << c;
        }
        cout << endl;
    }
}

const vector<tuple<int, int>> dirs = {
    make_tuple(1, 0),
    make_tuple(0, 1),
    make_tuple(-1, 0),
    make_tuple(0, -1),
};

void walkToTail(vector<vector<int>> &map, std::map<tuple<int, int>, int> &tailScores, tuple<int, int> start) {
    set<tuple<int, int>> explored;
    vector<tuple<int, int>> toCheck;
    explored.insert(start);
    toCheck.push_back(start);
    
    int rows = map.size();
    int cols = map[0].size();

    while (true) {
        int s = toCheck.size();
        if (s <= 0) {
            break;
        }

        tuple<int, int> check = toCheck[toCheck.size() - 1];
        toCheck.pop_back();

        int x = get<0>(check);
        int y = get<1>(check);
        int numAtCheck = map[y][x];
        
        for (tuple<int, int> dir : dirs) {
            int dx = get<0>(dir);
            int dy = get<1>(dir);

            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) {
                continue;
            }

            int numAtCheckOffset = map[ny][nx];
            tuple<int, int> coords = make_tuple(nx, ny);

            if (explored.count(coords) <= 0) {
                if (numAtCheck - 1 == numAtCheckOffset) {
                    if (numAtCheckOffset == 0) {
                        tailScores[coords] += 1;
                    } else {
                        toCheck.push_back(coords);
                    }
                    explored.insert(coords);
                }
            }


            // if (numAtCheck == 1) {
            //     if (explored.count(coords) <= 0) {
            //         if (numAtCheck - 1 == numAtCheckOffset) {
            //             toCheck.push_back(coords);
            //             explored.insert(coords);
            //         }
            //     }
            //     if (numAtCheckOffset == 0) {
            //         tailScores[coords] += 1;
            //     }
            // } else {
            //     if (explored.count(coords) <= 0) {
            //         if (numAtCheck - 1 == numAtCheckOffset) {
            //             toCheck.push_back(coords);
            //             explored.insert(coords);
            //         }
            //     }
            // }
        }
    }
}

int main() {
    ifstream InputFile("./input.txt");
    // ifstream InputFile("./test.txt");

    string cursor;

    vector< vector<int> > map;
    while (getline(InputFile, cursor)) {
        std::vector<char> row(cursor.begin(), cursor.end());
        vector<int> rowAsInts;
        for (char c : row) {
            int nc = c - '0';
            rowAsInts.push_back(nc);
        }
        map.push_back(rowAsInts);
    }
    printMap(map);

    int rows = map.size();
    int cols = map[0].size();

    vector<tuple<int, int>> startingPoints;
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            int c = map[y][x];
            if (c == 9) {
                tuple<int, int> tpt = make_tuple(x, y);
                startingPoints.push_back(tpt);
            }
        }
    }

    std::map<tuple<int, int>, int> tailScore;
    for (tuple<int, int> coords : startingPoints) {
        walkToTail(map, tailScore, coords);
    }

    int sum = 0;
    int tails = 0;
    cout << endl;
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            int c = map[y][x];
            if (c == 0) {
                tails += 1;
                tuple<int, int> tpt = make_tuple(x, y);
                int score = tailScore[tpt];
                cout << score << " ";
                sum += score;
            }
        }
    }
    cout << endl;
    // cout << tails << endl;
    
    cout << sum << endl;
    
    return 0;
}

