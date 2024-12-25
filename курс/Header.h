#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <string>

class Graph {
public:
    int V;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;

    Graph(int V);

    void addEdge(int u, int v, int cap);


    bool bfs(int source, int sink, std::vector<int>& parent);

    int edmondsKarp(int source, int sink);
    void printGraphvizToFile(const std::string& filename);
};

void readGraphFromFile(const std::string& filename, Graph& graph);

void writeResultToFile(const std::string& filename, int maxFlow);
