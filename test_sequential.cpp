#include <iostream>

#include "Graph.hpp"

template <typename T> void display (T* array, int length) {
    for (int i=0; i<length;i++) {
        std::cout << array[i] << " ";
    }

    std::cout << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    // Creating the graph
    std::ifstream file(argv[1]);
    Graph G(&file);
    file.close();

    G.display_graph();

    int parent[G.get_n()];
    std::cout << "Starting test" << std::endl;
    G.Dijkstra(0,parent);
    std::cout << "End of test" << std::endl;
    display(parent, G.get_n());
    return 0;
}