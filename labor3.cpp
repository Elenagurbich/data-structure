#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <windows.h>

using namespace std;

bool hasCycle(const unordered_map<char, vector<char>>& graph, unordered_set<char>& visited, unordered_set<char>& recStack, char node) {
    if (recStack.find(node) != recStack.end()) return true;
    if (visited.find(node) != visited.end()) return false;

    visited.insert(node);
    recStack.insert(node);

    for (char neighbor : graph.at(node)) {
        if (hasCycle(graph, visited, recStack, neighbor)) {
            return true;
        }
    }

    recStack.erase(node);
    return false;
}

bool isConsistent(const unordered_map<char, vector<char>>& graph, const unordered_set<char>& nodes) {
    unordered_set<char> visited;
    unordered_set<char> recStack;

    for (char node : nodes) {
        if (visited.find(node) == visited.end()) {
            if (hasCycle(graph, visited, recStack, node)) {
                return false;
            }
        }
    }
    return true;
}

vector<char> topologicalSort(const unordered_map<char, vector<char>>& graph, const unordered_set<char>& nodes) {
    unordered_map<char, int> inDegree;
    for (char node : nodes) {
        inDegree[node] = 0;
    }

    for (const auto& pair : graph) {
        for (char neighbor : pair.second) {
            inDegree[neighbor]++;
        }
    }

    queue<char> q;
    for (char node : nodes) {
        if (inDegree[node] == 0) {
            q.push(node);
        }
    }

    vector<char> sortedList;
    while (!q.empty()) {
        char node = q.front();
        q.pop();
        sortedList.push_back(node);

        for (char neighbor : graph.at(node)) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return sortedList;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cin >> N;

    unordered_map<char, vector<char>> graph;
    unordered_set<char> nodes;

    for (int i = 0; i < N; ++i) {
        char a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        nodes.insert(a);
        nodes.insert(b);
    }

    if (!isConsistent(graph, nodes)) {
        cout << "Противоречивая последовательность" << endl;
        return 0;
    }

    vector<char> sortedList = topologicalSort(graph, nodes);
    if (sortedList.size() != nodes.size()) {
        cout << "Неполная последовательность" << endl;
    }
    else {
        cout << "Полная последовательность: ";
        for (char c : sortedList) {
            cout << c << " ";
        }
        cout << endl;
    }

    return 0;
}