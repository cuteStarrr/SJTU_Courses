
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#include "righttriangle.h"

//------------------------------------------------------------------------------

int main()
{
    Point P1(300 - 71, 200 - 171);
    Point P2(300 + 71, 200 - 171);
    Point P3(300 + 171, 200 - 71);
    Point P4(300 + 171, 200 + 71);
    Point P5(300 + 71, 200 + 171);
    Point P6(300 - 71, 200 + 171);
    Point P7(300 - 171, 200 + 71);
    Point P8(300 - 171, 200 - 71);
    Point P9(300, 200 - 71);
    Point P10(300, 200 + 71);

    Righttriangle tg1(P1, P9, P8);
    Righttriangle tg2(P9, P1, P2);
    Righttriangle tg3(P2, P9, P3);
    Righttriangle tg4(P3, P4, P8);
    Righttriangle tg5(P7, P8, P4);
    Righttriangle tg6(P6, P10, P7);
    Righttriangle tg7(P10, P6, P5);
    Righttriangle tg8(P5, P10, P4);

    Color col_tg1 = Color::yellow;
    Color col_tg2 = Color::red;
    Color col_tg3 = Color::magenta;
    Color col_tg4 = Color::green;
    Color col_tg5 = Color::cyan;
    Color col_tg6 = Color::blue;
    Color col_tg7 = Color::dark_red;
    Color col_tg8 = Color::dark_green;

    Point tl(100,100);           // to become top left  corner of window
    Simple_window win(tl,600,400,"Canvas");    // make a simple window

    tg1.DrawRT(col_tg1, win);
    tg2.DrawRT(col_tg2, win);
    tg3.DrawRT(col_tg3, win);
    tg4.DrawRT(col_tg4, win);
    tg5.DrawRT(col_tg5, win);
    tg6.DrawRT(col_tg6, win);
    tg7.DrawRT(col_tg7, win);
    tg8.DrawRT(col_tg8, win);

    win.wait_for_button();       // give control to the display engine

}

//------------------------------------------------------------------------------
