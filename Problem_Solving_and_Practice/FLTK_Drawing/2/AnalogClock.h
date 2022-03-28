#ifndef ANALOGCLOCK_H_INCLUDED
#define ANALOGCLOCK_H_INCLUDED

#include <fstream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities

using namespace std;
using namespace Graph_lib;   // our graphics facilities are in Graph_lib

class AnalogClock {
    private:
    Circle clock;
    Circle orig;

    public:
    AnalogClock(Point P, int r1, int r2, Simple_window & win):clock(P, r1), orig(P,r2){
        win.attach(clock);
        win.attach(orig);
        for(int i = 1; i <= 12; ++i) {
            Text * hour;
            Line * mark;
            hour = new Text(Point(int(198 + 80 * sin(30 * 3.14159 / 180 * i)), int(205 - 80 * cos(30 * 3.14159 / 180 * i))), to_string(i));
            (*hour).set_font_size(12);
            mark = new Line(Point(Point(int(200 + 90 * sin(30 * 3.14159 / 180 * i)), int(200 - 90 * cos(30 * 3.14159 / 180 * i)))), Point(Point(int(200 + 100 * sin(30 * 3.14159 / 180 * i)), int(200 - 100 * cos(30 * 3.14159 / 180 * i)))));
            win.attach(*hour);
            win.attach(*mark);
        }
    }
    void ShowTime(Simple_window & win);
};


#endif // ANALOGCLOCK_H_INCLUDED