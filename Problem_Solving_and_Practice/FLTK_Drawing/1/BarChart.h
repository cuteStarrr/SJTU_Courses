#ifndef BARCHART_H_INCLUDED
#define BARCHART_H_INCLUDED

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities

using namespace std;
using namespace Graph_lib;   // our graphics facilities are in Graph_lib

class BarChart {
    private:
    int start;
    int width;
    int scale; // times data will be stretched
    int dist;
    vector<double> data;
    Polygon bars;
    public:
    BarChart(int s, int w, int sc, int d, vector<double> & temp):start(s), width(w), scale(sc), dist(d) {
        for(int i = 0; i < temp.size(); ++i) {
            data.push_back(temp[i]);
        }
    }
    void DrawBar(Point o, Color col, Simple_window & window);
};

#endif // BARCHART_H_INCLUDED