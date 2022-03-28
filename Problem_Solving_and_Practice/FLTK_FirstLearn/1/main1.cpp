
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
/*
#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
*/
#include "hyperelliptic.h"

//------------------------------------------------------------------------------

int main()
{
    int a;
    int b;
    int m;
    int n;
    int N;

    cin >> a;
    cin >> b;
    cin >> m;
    cin >> n;
    cin >> N;

    Hyperelliptic star(a, b, m, n, N);

    star.DrawStar();
}

//------------------------------------------------------------------------------
