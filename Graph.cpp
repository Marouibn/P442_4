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
#include <queue> // For priority queue
#include <vector> // For vector
#include <cfloat> // For DBL_MAX
#include <time.h> // For srand seed
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Graph.hpp"
#include "Arc.hpp"

void display_arc(int source, int destination, double cost) {
    std::cout << source << "-->" << destination << " : " << cost << std::endl;
}


template <typename T> void display (T* array, int length) { // To remove !!
    for (int i=0; i<length;i++) {
        std::cout << array[i] << " ";
    }

    std::cout << std::endl;
}

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

Graph::Graph(std::ifstream *file, int directed) {
    if (directed != 0) {
        std::cerr << "directed must be given value 0, otherwise use constructor Graph::Graph(std::ifstream * file)" << std::endl;
    }
    // Getting the basic information about the graph
    *file >> n;
    *file >> m;
    m *= 2;
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
    double cost;
    for (int i = 0; i<m/2;i++) {
        //std::cout << "Trying some stuff" << std::endl;
        *file >> source;
        source--;
        *file >> destination;
        destination--;
        *file >> cost;
        Adjacency[source][destination] = cost;
        Adjacency[destination][source] = cost;
        for (int j=0; j<k;j++) {
            *file >> cost;
            arcs_consumption[source][destination][j] = cost;
            arcs_consumption[destination][source][j] = cost;
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

int Graph::get_m() {
    return m;
}

double Graph::get_cost(int start, int end) {
    return Adjacency[start][end];
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

void Graph::Dijkstra(int source, int* parent) {
    double distance[n];
    for (int i=0; i<n;i++) {
        distance[i] = DBL_MAX;
    }
    distance[source] = 0;

    for (int i=0; i<n;i++) {
        parent[i] = -1;
    }
    parent[source] = source;

    // Creating the priority queue
    //auto Compare = [] (Arc &a, Arc &b) {return a.get_cost()>b.get_cost();};
    std::priority_queue<Arc, std::vector<Arc>, decltype( Compare ) > pq( Compare );
    std::cout << "Succesfully created priority queue !" << std::endl;

    // Adding the arcs from source to the queue
    for (int i=0;i<n;i++) {
        if (get_cost(source,i)>=0) {
            pq.emplace(source, i, get_cost(source,i));
            std::cout << "Emplacing: ";
            display_arc(source, i, get_cost(source,i));
        }
    }

    // Running a loop until the queue is empty
    while (!pq.empty()) {
        Arc arc = pq.top();

        if (parent[arc.get_end()] != -1) { // If the vertex has already been visited
            std::cout << "Popping: ";
            display_arc(pq.top().start, pq.top().end,pq.top().cost);
            pq.pop();
            continue;
        }

        parent[arc.get_end()] = arc.get_start();
        distance[arc.get_end()] = arc.get_cost();
        
        std::cout << "Popping: ";
        display_arc(pq.top().start, pq.top().end,pq.top().cost);
        display(parent,n);
        pq.pop();

        // Adding all the neighbors of the newly added arc to the priority queue
        for (int i=0; i<n;i++) {
            if (get_cost(arc.get_end(), i)>=0 && parent[i]==-1) {
                pq.emplace(arc.get_end(),i, distance[arc.get_end()]+get_cost(arc.get_end(), i));
                std::cout << "Emplacing: ";
                display_arc(arc.get_end(), i, distance[arc.get_end()]+get_cost(arc.get_end(), i));
            }
        }
    }
}

//auto Compare = [] (Arc &a, Arc &b) {return a.get_cost()>b.get_cost();};


void Graph::parallel_thread_func(int index, int n_pu,std::priority_queue<Arc, std::vector<Arc>, decltype( Compare )> &q,std::priority_queue<Arc, std::vector<Arc>, decltype( Compare )> &qstar, int* ind,double threshold, std::vector<Arc*> &Req, double *tent, int* dequeued, int* closest_out, double* delta_out, std::vector<Arc>* B, std::mutex &mx, int &step23, int &step4, std::condition_variable &cond23, std::condition_variable &cond4) {
    // Step 1 is done outside of the threads

    // Step 2 and 3
    while (q.top().cost > threshold) {
        const Arc* parc = &q.top();
        int vertex = parc->end;
        for(int w=0;w<n;w++) {
            mx.lock();
            if (Adjacency[vertex][w] != -1.0)
                Req.push_back(new Arc(vertex, w, parc->cost+Adjacency[vertex][w]));
            mx.unlock();
        }
    }
    step23++;
    cond23.notify_one();
    //Making sure all the threads have goen through steps 2 and 3
    std::unique_lock<std::mutex> ul(mx);
    cond23.wait(ul, [step23, n_pu] { return (step23 == n_pu) ? true : false;});
    cond23.notify_all();

    // One thread performs step 4 - The first one that got notified works
    if (!step4) {
        step4++;
        for (int i=0; i<Req.size();i++) {
            B[ind[Req[i]->end]].push_back(*Req[i]);
        }
    }
    ul.unlock();

    for (int i=0;i<B[index].size();i++) {
        int vertex = B[index][i].end;
        if (B[index][i].cost < tent[vertex]) {
            tent[vertex] = B[index][i].cost;
            q.emplace(B[index][i].start,B[index][i].end,B[index][i].cost);
            if (!closest_out[vertex]) { // We haven't yet computed the closest outgoing neighbor, we compute it
                int closest = 0;
                double distance = Adjacency[vertex][0];
                for (int j=1; j<n;j++) {
                    if (Adjacency[vertex][j] >= -1.0 && Adjacency[vertex][j] < distance) {
                        closest = j;
                        distance = Adjacency[vertex][j];
                    }
                }
                closest_out[vertex] = closest;
                delta_out[vertex] = distance;
            }
            qstar.emplace(vertex, closest_out[vertex], tent[vertex]+delta_out[vertex]);
        }
    }
}

void Graph::parallel_SSSP(int source, int* parent, int n_pu) {
    // Define which PU deals with which node. ind[i] is the PU that deals with vertex i
    // Each vertex is randomly given to a PU from 0 to n_pu-1
    int ind[n];
    srand(time(NULL));
    for (int i=0; i<n;i++) {
        ind[i] = rand()%n_pu;
    }
    
    // Creating the queues
    //auto Compare = [] (Arc &a, Arc &b) {return a.get_cost()>b.get_cost();};
    std::priority_queue<Arc, std::vector<Arc>, decltype( Compare )>* Q[n_pu];
    std::priority_queue<Arc, std::vector<Arc>, decltype( Compare )>* Qstar[n_pu];
    for (int i=0;i<n_pu;i++) {
        Q[i] = new std::priority_queue<Arc, std::vector<Arc>, decltype(Compare)> (Compare);
        Qstar[i] = new std::priority_queue<Arc, std::vector<Arc>, decltype(Compare)> (Compare);
    }

    // The list of requests, ie: deleted nodes
    std::vector<Arc>* Req;

    // A list to keep tentative distances - Useful since there is no DecreaseKey
    double tent[n];
    for (int i=0;i<n;i++) {
        tent[i] = DBL_MAX;
    }

    // A list of buffer arrays of step 4
    std::vector<Arc> B[n_pu];

    // A vector to keep the distance to closest outgoing neighbor, and a vector of indexes of closest outgoing neighbors
    double delta_out[n];
    int closest_out[n];
    for (int i=0; i<n;i++) {
        delta_out[i] = NULL;
        closest_out[i] = NULL;
    }

    // A vector to check if member has been dequeued - Since we have no decreasekey
    int dequeued[n];
    for (int i=0; i<n;i++) {
        dequeued[i] = 0; // Initially no element has been dequeued
    }

    // Initializing the queues
    Q[ind[source]]->emplace(source, source, 0);
    Qstar[ind[source]]-> emplace(source, source, 0); // a modifier


    // Creating the threads, the mutex
    std::thread threads[n_pu];
    std::mutex mx;

    // Creating the condition variables
    int step23 = 0;
    int step4 = 0;
    std::condition_variable cond23; // Verifies that all the threads have done the steps 2 and 3
    std::condition_variable cond4; // Verifies that step 3 is over
    
    /*while (1) {
        // Step 1: We look for the minimal 
        find_min();
        // 
        for (int i=0; i<n_pu; i++) {
            threads[i] = pthread_create(Thefunction, theArgs, double threshold);
        }
    }*/

}

void Graph::set_cost(int start, int end, double cost) {
    Adjacency[start][end] = cost;
}


void Graph::get_path(int destination, int* parent) {
    std::vector<int> path;
    while (destination != parent[destination]) {
        path.push_back(destination);
        destination = parent[destination];
    }
    path.push_back(destination);
    int len = path.size();
    for (int i=0;i<len;i++) {
        std::cout << path[len-i-1] << " ";
    }
    std::cout << std::endl;
}