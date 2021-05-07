#include <iostream>
#include <cfloat>

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
    Graph G(&file,0);
    file.close();

    //G.display_graph();

    int parent[G.get_n()];
    std::cout << "Starting test" << std::endl;
    G.Dijkstra(1,parent);
    std::cout << "End of test" << std::endl;
    display(parent, G.get_n());

    G.get_path(0, parent);
    /*Graph G(5,7,0);
    G.set_cost(0,1,6.0);
    G.set_cost(1,0,6.0);
    G.set_cost(0,4,1.0);
    G.set_cost(4,0,1.0);
    G.set_cost(4,1,2.0);
    G.set_cost(1,4,2.0);
    G.set_cost(4,3,1.0);
    G.set_cost(3,4,1.0);
    G.set_cost(1,3,2.0);
    G.set_cost(3,1,2.0);
    G.set_cost(1,2,5.0);
    G.set_cost(2,1,5.0);
    G.set_cost(2,3,5.0);
    G.set_cost(3,2,5.0);
    
    //G.display_graph();

    int parent[5];

    G.Dijkstra(0, parent);

    display(parent, 5);

    std::cout << "The path from 0 to 2" << std::endl;
    G.get_path(2,parent);*/

    return 0;
}