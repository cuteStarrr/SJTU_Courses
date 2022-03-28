#ifndef HYPERELLIPTIC_H_INCLUDED
#define HYPERELLIPTIC_H_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities

using namespace std;
using namespace Graph_lib;   // our graphics facilities are in Graph_lib

class Hyperelliptic {
    private:
        int a;
        int b;
        int m;
        int n;
        int N;
    public:
        Hyperelliptic(int aa = 1, int bb = 1, int mm = 1, int nn = 1, int NN = 2) {a = aa; b = bb; m = mm; n = nn; N = NN;}
        int GetPositiveY(int x);
        void DrawStar();
};

#endif // HYPERELLIPTIC_H_INCLUDED