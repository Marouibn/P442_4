#pragma once
#include <iostream>

class Arc {
    int start;
    int end;
    double cost;
    
    public:
        Arc(int _start, int _end, double _cost);
};