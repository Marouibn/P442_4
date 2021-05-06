#include <iostream>

#include "Graph.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream file(argv[1]);

    Graph G(&file);
    file.close();
    std::cout << "The end" << std::endl;

    return 0;
}