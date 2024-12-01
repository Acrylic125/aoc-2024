#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <map>

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

int main() {
    ifstream InputFile("./input.txt");

    string cursor;

    vector<int> l1;
    vector<int> l2;

    while (getline(InputFile, cursor)) {
        vector<string> lineSplit = split(cursor, delimiter);
        int i1 = stoi(lineSplit[0]);
        int i2 = stoi(lineSplit[1]);
        // cout << i1 << " " << i2 << endl;
        l1.push_back(i1);
        l2.push_back(i2);
    }

    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());

    map<string, int> occurenceCountMap;
    for (int i = 0; i < l2.size(); i++) {
        occurenceCountMap[to_string(l2[i])] += 1;
    }

    int totalDistance = 0;
    int s = l1.size();
    for (int i = 0; i < s; i++) {
        int i1 = l1[i];

        int m = occurenceCountMap[to_string(i1)];
        totalDistance += i1 * m;
    }
    cout << totalDistance;

    return 0;
}

