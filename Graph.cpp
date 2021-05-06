/**
 * INF442: Algorithms for data analysis in C++
 * Project P442_4
 * 
 * Instructor: Simon Bliudze <simon.bliudze@inria.fr>
 * 
 * @file Graph.cpp
 * @author Marouane IBN BRAHIM, Omar BENNOUNA
 * @version May 2021
 */

#include <iostream>
#include <string>
#include <queue>

#include "Graph.hpp"
#include "Arc.hpp"

Graph::Graph(int _n, int _m, int _k) {
    n = _n;
    m = _m;
    k = _k;

    res_upper_lim = new double[k];
    res_lower_lim = new double[k];
    Adjacency = new double* [n];
    nodes_consumption = new double* [n];
    arcs_consumption = new double** [n];

    for (int i=0; i<n;i++) {
        Adjacency[i] = new double[n];
        nodes_consumption[i] = new double [k];
        arcs_consumption[i] = new double* [n];
        for (int j=0; j<n;j++) {
            Adjacency[i][j] = -1.0;
            arcs_consumption[i][j] = new double [k];
            for (int l=0;l<k;l++) {
                arcs_consumption[i][j][l] = -1.0;
            }
        }
    }
}

Graph::Graph(std::ifstream *file) {
    // Getting the basic information about the graph
    *file >> n;
    *file >> m;
    *file >> k;

    std::cout << "The number of edges: " << n << "\nThe number of arcs: " << m << "\nThe number of resources: " << k << std::endl;

    // Start by declaring all the attributes
    // And initializing the Adjacency and arcs_consumption matrices to -1
    res_upper_lim = new double[k];
    res_lower_lim = new double[k];
    Adjacency = new double* [n];
    nodes_consumption = new double* [n];
    arcs_consumption = new double** [n];

    for (int i=0; i<n;i++) {
        Adjacency[i] = new double[n];
        nodes_consumption[i] = new double [k];
        arcs_consumption[i] = new double* [n];
        for (int j=0; j<n;j++) {
            Adjacency[i][j] = -1.0;
            arcs_consumption[i][j] = new double [k];
            for (int l=0;l<k;l++) {
                arcs_consumption[i][j][l] = -1.0;
            }
        }
    }

    // Getting the lower limit on each resource from file
    for (int i=0; i<k; i++) {
        //std::cout << "Succesfully added stuff !" << std::endl;
        *file >> res_lower_lim[i];
    }

    // Getting the upper limit on each resource from file
    for (int i=0; i<k; i++) {
        *file >> res_upper_lim[i];
    }

    // Getting the amount of resource consumed when passing through vertices
    for (int i=0; i<n;i++) {
        for (int j=0; j<k;j++) {
            *file >> nodes_consumption[i][j];
        }
    }

    // Getting the cost of each arc and resources consumed
    int source;
    int destination;
    int counter = 0;
    for (int i = 0; i<m;i++) {
        //std::cout << "Trying some stuff" << std::endl;
        *file >> source;
        source--;
        *file >> destination;
        destination--;
        *file >> Adjacency[source][destination];
        for (int j=0; j<k;j++) {
            *file >> arcs_consumption[source][destination][j];
        }
    }
}

Graph::~Graph() {
    for (int i=0; i<n; i++) {
        delete[] Adjacency[i];
        delete[] nodes_consumption[i];
        for (int j=0;j<n;j++) {
            delete[] arcs_consumption[i][j];
        }
        delete[] arcs_consumption[i];
    }
    delete[] res_upper_lim;
    delete[] res_lower_lim;
    delete[] Adjacency;
    delete[] nodes_consumption;
}

int Graph::get_n() {
    return n;
}

int Graph::get_k() {
    return k;
}

void Graph::display_graph() {
    std::cout << n << " " << m << " " << k << std::endl;
    for (int i=0; i<k;i++) {
        std::cout << res_lower_lim[i] << " ";
    }
    std::cout << std::endl;

    for (int i=0; i<k;i++) {
        std::cout << res_upper_lim[i] << " ";
    }
    std::cout << std::endl;

    for (int i=0; i<n; i++) {
        for (int j=0; j<k;j++) {
            std::cout << nodes_consumption[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n;j++) {
            if (Adjacency[i][j] != -1) {
                std::cout << i+1 << " " << j+1 << " " << Adjacency[i][j] << " ";
                for (int l=0; l<k;l++) {
                    std::cout << arcs_consumption[i][j][l] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

void Graph::Dijkstra(int source, int destination) {
    auto Compare = [] (Arc &a, Arc &b) {return a.get_cost()<b.get_cost();};

    std::priority_queue<Arc, std::vector<Arc>, decltype(Compare)> pq(Compare);
    std::cout << "Succesfully created priority queue !" << std::endl;

    
}