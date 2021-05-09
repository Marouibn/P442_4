#pragma once
#include <iostream>

class Arc {
    public:
        int start;
        int end;
        double cost;
        Arc(int _start, int _end, double _cost); 
        int get_start();
        int get_end();
        double get_cost();
        void diplay();
};

auto Compare = [] (Arc &a, Arc &b) {return a.get_cost()>b.get_cost();};
