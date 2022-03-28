#include"righttriangle.h"

Righttriangle::Righttriangle(Point AA, Point BB, Point CC) {
    A = AA; B = BB; C = CC;
    triangle.add(A);
    triangle.add(B);
    triangle.add(C);
}


Righttriangle::Righttriangle(Point AA, int AB, int AC) {
    Point BB(AA.x, AA.y + AB);
    Point CC(AA.x + AC, AA.y);
    Righttriangle(AA,BB,CC);
}


void Righttriangle::DrawRT(Color col, Simple_window & w) {
    triangle.set_color(col);
    triangle.set_fill_color(col);
    w.attach(triangle);
}