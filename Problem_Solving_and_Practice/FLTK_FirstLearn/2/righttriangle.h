#ifndef RIGHTTRIANGLE_H_INCLUDED
#define RIGHTTRIANGLE_H_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities

using namespace std;
using namespace Graph_lib;   // our graphics facilities are in Graph_lib

class Righttriangle {
    private:
        Point A;
        Point B;
        Point C;
        Polygon triangle;
    public:
        Righttriangle(Point AA, Point BB, Point CC);
        Righttriangle(Point AA, int AB, int AC);
        void DrawRT(Color col, Simple_window & w);
};

#endif //RIGHTTRIANGLE_H_INCLUDED