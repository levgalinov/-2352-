#include <iostream>
#include "Header.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");


    if (argc != 1) {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    std::string inputFilename = "input.txt";
    std::string outputFilename = "output.txt";

    int source, sink;
    std::cout << "������� �������� �������: ";
    std::cin >> source;
    std::cout << "������� �������� �������: ";
    std::cin >> sink;

    Graph graph(0);
    readGraphFromFile(inputFilename, graph);


    int maxFlow = graph.edmondsKarp(source, sink);

    writeResultToFile(outputFilename, maxFlow);

    std::string outputDotFilename = "max_flow_network.dot";
    graph.printGraphvizToFile(outputDotFilename);

    return 0;
}