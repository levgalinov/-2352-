#include "Header.h"


Graph::Graph(int V) {
    this->V = V;
    capacity.resize(V, std::vector<int>(V, 0));
    flow.resize(V, std::vector<int>(V, 0));
}


void Graph::addEdge(int u, int v, int cap) {
    capacity[u][v] += cap;
}


bool Graph::bfs(int source, int sink, std::vector<int>& parent) {
    std::vector<bool> visited(V, false);
    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
                if (v == sink) return true;
            }
        }
    }
    return false;
}

int Graph::edmondsKarp(int source, int sink) {
    int maxFlow = 0;
    std::vector<int> parent(V);

    while (bfs(source, sink, parent)) {
        int pathFlow = INT_MAX;

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, capacity[u][v] - flow[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += pathFlow;
            flow[v][u] -= pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}


void Graph::printGraphvizToFile(const std::string& filename) {
    std::ofstream out(filename);
    out << "digraph G {" << std::endl;
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (capacity[u][v] > 0) {
                out << "\t" << u << " -> " << v
                    << " [label=\"Cap: " << capacity[u][v]
                    << ", flow: " << flow[u][v] << "\"];" << std::endl;
            }
        }
    }
    out << "}" << std::endl;
    out.close();
}


void readGraphFromFile(const std::string& filename, Graph& graph) {
    std::ifstream infile(filename);
    int V, E;
    infile >> V >> E;
    graph = Graph(V);

    for (int i = 0; i < E; i++) {
        int u, v, cap;
        infile >> u >> v >> cap;
        graph.addEdge(u, v, cap);
    }
}


void writeResultToFile(const std::string& filename, int maxFlow) {
    std::ofstream out(filename);
    out << "Максимальный поток: " << maxFlow << std::endl;
    out.close();
}