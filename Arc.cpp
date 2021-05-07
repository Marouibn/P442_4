#include <iostream>

#include "Arc.hpp"

Arc::Arc(int _start, int _end, double _cost) {
    start = _start; // The start node of t
    end=  _end;
    cost = _cost;
    int n_resources;
    double* consumption;
}

int Arc::get_start() {
    return start;
}

int Arc::get_end() {
    return end;
}

double Arc::get_cost() {
    return cost;
}

void Arc::diplay() {
    std::cout << start << "-->" << end << " : " << cost << std::endl;
}