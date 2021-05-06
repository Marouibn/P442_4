#include <iostream>

#include "Graph.hpp"

void display(double* array, int length) {
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

    std::ifstream file(argv[1]);
    Graph G(&file);
    file.close();

    G.display_graph();
    return 0;
}