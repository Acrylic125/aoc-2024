#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <iostream>
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

struct Ref {
    vector<string> next;
};

bool findSubgraph(Ref cur, vector<string> subgraph, map<string, Ref> graph, int i) {
    if (i >= (subgraph.size() - 1)) {
        return true;
    }
    string node = subgraph[i];
    if (graph.count(node) <= 0) {
        return false;
    }

    vector<string> next = cur.next; // graph[node].next;
    if (next.size() <= 0) {
        return false;
    }

    string nodeNext = subgraph[i + 1];
    for (string n : next) {
        if (graph.count(n) <= 0) {
            return false;
        }

        if (n == nodeNext) {
            bool found = findSubgraph(graph[n], subgraph, graph, i + 1);
            if (found) return true;
        } else {
            bool found = findSubgraph(graph[n], subgraph, graph, i);
            if (found) return true;
        }
    }

    return false;
}

int main() {
    ifstream InputFile("./input.txt");
    // ifstream InputFile("./test.txt");

    string cursor;

    int mode = 0;
    map<string, Ref> refMap;

    int sum = 0;

    while (getline(InputFile, cursor)) {
        if (cursor == "") {
            mode = 1;
            continue;
        }
        if (mode == 0) {
            vector<string> s = split(cursor, "|");
            int high = stoi(s[0]);
            int low = stoi(s[1]);

            string lowKey = to_string(low);
            string highKey = to_string(high);

            Ref lowRef, highRef;
            
            if (refMap.count(lowKey) > 0) {
                 lowRef = refMap[lowKey];
            }
            if (refMap.count(highKey) > 0) {
                 highRef = refMap[highKey];
            }

            highRef.next.push_back(lowKey);

            refMap[lowKey] = lowRef;
            refMap[highKey] = highRef;
        } else {
            vector<string> s = split(cursor, ",");
            cout << cursor << endl;
            bool isValid = findSubgraph(refMap[s[0]], s, refMap, 0);
            if (isValid) {
                cout << "Valid" << endl;
                int middleIndex = s.size() / 2;
                int smid = stoi(s[middleIndex]);
                sum += smid;
            }
        }
    }

    // vector<string> t = refMap["29"].next;
    // cout << "GGGG: " << t.size() << "   " << t[0] << endl;

    cout << sum;
    return 0;
}

