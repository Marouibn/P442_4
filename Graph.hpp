/**
 * INF442: Algorithms for data analysis in C++
 * Project P442_4
 * 
 * Instructor: Simon Bliudze <simon.bliudze@inria.fr>
 * 
 * @file Graph.hpp
 * @author Marouane IBN BRAHIM, Omar BENNOUNA
 * @version May 2021
 */

#pragma once
#include <iostream>
#include <fstream>

#include "Arc.hpp"

/**
 * We are going to use an adjacency matrix representation of the graph
 *
 * It allow to find the neighbors of each vertex in O(n).
 *
 * The adjacency matrix will be represented by a 2-dimensional array of doubles
 *
 * The cell [i][j] contains cost of directed edge i->j if exists, -1 otherwise
 * 
 */
class Graph {
    // Number of vertices in the graph
    int n;

    // Number of Arcs in the graph
    int m;

    // The number of different types of resources of the gragh
    int k;

    // The adjacency matrix
    double** Adjacency;

    // An array containing the available quantity of each resource (dimension = n_resources)
    double* res_quantity;

    // The cost of traversing each node: The cell [i][j] represents how much of resource j in costs to pass through vertex i
    double** nodes_consumption;

    public:
        Graph(std::ifstream * file); // Constructs a graph from a file of type "rcsp"
        Graph(int _n, int _m, int _k); // Constructs an empty graph
        ~Graph();
        
        /**
         * Getter function for the number of vertices
         * 
         * @returns The number of nodes n
         */
        int get_n_nodes();

        /**
         * Getter for the number of resources
         * 
         * @returns The number of vertices
         */
        int get_n_resources();

        /**
         * Loads the data form a file into the graph class
         * The files format supported is described in this source :
         * http://people.brunel.ac.uk/~mastjjb/jeb/orlib/rcspinfo.html
         * here is a brief description of file format
         * 
         *          Number of Vertices   |   Number of Arcs   |   Number of resources
         *          For each resource, lower limit 
         *          For each resource higher limit
         *          For each vertex, the amount of each resource consumed when passing through the vertex
         *          For each arc: source | Destination | Cost | For each resource the amount consumed in the arc
         * 
         * @param file An ifstream object representing a file that contains the data
         */
        void load(std::ifstream* file); // Set to load files of type "rcsp" 


};