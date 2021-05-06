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

    // The lower limit for each resource on the chosen path
    double* res_upper_lim;

    // The lower limit for each resource on the chosen path
    double* res_lower_lim;

    // The cost of traversing each node: The cell [i][j] represents how much of resource j in costs to pass through vertex i
    double** nodes_consumption;

    // The cost of traversing an arc: The cell [i][j][k] represents how much of resource k is consumed when passing through arc of source i and destination j
    double*** arcs_consumption;


    public:

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
        Graph(std::ifstream * file); // Constructs a graph from a file of type "rcsp"
        Graph(int _n, int _m, int _k); // Constructs an empty graph
        ~Graph();
        
        /**
         * Getter function for the number of vertices
         * 
         * @returns The number of nodes n
         */
        int get_n();

        /**
         * Getter for the number of arcs
         * 
         * @returns The number of arcs
         */
        int get_m();

        /**
         * Getter for the number of resources
         * 
         * @returns The number of vertices
         */
        int get_k();

        /**
         * Getter for the cost of the edge from start to end
         * If no edge exists from start to end, return -1
         * 
         * @param start An integer representing the index of the start
         * @param end An integer representing the index of the end
         * @returns The cost of arc i->j, -1 if no such arc exists
         */
        double get_cost(int start, int end);

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


        /**
         * Applies Dijkstra's Algorithm on the graph
         * @param source the index of the source vertex
         * @param destination the index of the destination vertex
         * @return Yet to define
         */
        void Dijkstra(int source, int* parent);

        /**
         * Displays the file as it is given before loading it
         * For debugging
         */
        void display_graph();
};