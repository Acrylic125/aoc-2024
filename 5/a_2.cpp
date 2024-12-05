#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <iostream>
#include <map>
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

int main() {
    ifstream InputFile("./input.txt");
    // ifstream InputFile("./test.txt");

    string cursor;

    map<string, set<string>> refMap;

    int sum = 0;

    bool update = false;
    while (getline(InputFile, cursor)) {
        if (cursor == "") {
            update = true;
            continue;
        }
        if (update) {
            vector<string> s = split(cursor, ",");
            cout << cursor << endl;

            vector<string> prev;
            bool shouldCount = true;
            for (string num : s) {
                set<string> deps;
                if (refMap.count(num) > 0) {
                    deps = refMap[num];
                }

                if (prev.size() > 0) {
                    bool found = true;
                    for (string p : prev) {
                        if (deps.count(p) <= 0) {
                            found = false;
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Not found!" << endl;
                        shouldCount = false;
                        break;
                    }
                }

                prev.push_back(num);
            } 

            if (shouldCount) {
                cout << "Valid" << endl;
                int middleIndex = s.size() / 2;
                int smid = stoi(s[middleIndex]);
                sum += smid;
            }
        } else {
            vector<string> s = split(cursor, "|");
            string before = s[0];
            string after = s[1];

            set<string> depsBefore;
            set<string> depsAfter;

            if (refMap.count(before) > 0) {
                depsBefore = refMap[before];
            }
            if (refMap.count(after) > 0) {
                depsAfter = refMap[after];
            }

            depsAfter.insert(before);
            for (string dep : depsBefore) {
                depsAfter.insert(dep);
            }

            refMap[before] = depsBefore;
            refMap[after] = depsAfter;
        }
    }

    cout << sum;
    return 0;
}

