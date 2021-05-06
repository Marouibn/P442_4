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

#include "Graph.hpp"

Graph::Graph(int _n, int _m, int _k) {
    n = _n;
    m = _m;
    k = _k;

    Adjacency = new double* [n];
    res_quantity = new double[k];
    nodes_consumption = new double* [n];

    for (int i=0; i<n;i++) {
        Adjacency[i] = new double[n];
        nodes_consumption[i] = new double [n];
    }
}

Graph::Graph(std::ifstream *file) {
    // Getting the basic information about the graph
    *file >> n;
    *file >> m;
    *file >> k;

    std::cout << n << m << k << std::endl;
    // Start by declaring all the attributes
    Adjacency = new double* [n];
    res_quantity = new double[k];
    nodes_consumption = new double* [n];

    for (int i=0; i<n;i++) {
        Adjacency[i] = new double[n];
        nodes_consumption[i] = new double [k];
    }
}

Graph::~Graph() {
    for (int i=0; i<n; i++) {
        delete[] Adjacency[i];
        delete[] nodes_consumption[i];
    }
    delete[] res_quantity;
    delete[] Adjacency;
    delete[] nodes_consumption;
}

int Graph::get_n() {
    return n;
}

int Graph::get_k() {
    return k;
}