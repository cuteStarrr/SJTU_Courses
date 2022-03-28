#include"hyperelliptic.h"

int Hyperelliptic::GetPositiveY(int x) {
    float y = 1 - pow(x / a, m);
    y = pow(y, 1/n);
    y = b * y;
    return int(y);
}

void Hyperelliptic::DrawStar() {
    int block;
    block = int(2 * a / ((N - 2) / 2 + 1));
    int x = a - block;
    int y;

    Point tl(0,0);           // to become top left  corner of window

    Simple_window win(tl,600,400,"Canvas");    // make a simple window

    vector<Point> points;                // make a shape (a polygon)
    Lines line;

    Point next_pos (a + 300, 200);  // 300 200 : translate the graph to the center
    points.push_back(next_pos);
    for(int i = 0; i < points.size() - 1; ++i) {
        line.add(next_pos, points[i]);
    }
    Point next_neg(-a + 300, 200);
    points.push_back(next_neg);
    for(int i = 0; i < points.size() - 1; ++i) {
        line.add(next_neg, points[i]);
    }

    while(x > -a + block / 2) {
        y = GetPositiveY(x);
        Point next_pos (x + 300, y + 200);
        points.push_back(next_pos);
        for(int i = 0; i < points.size() - 1; ++i) {
            line.add(next_pos, points[i]);
        }
        Point next_neg(x + 300, -y + 200);
        points.push_back(next_neg);
        for(int i = 0; i < points.size() - 1; ++i) {
            line.add(next_neg, points[i]);
        }
        x -= block;
    }

    line.set_color(Color::red);  // adjust properties of poly

    //win.attach (poly);           // connect poly to the window

    win.attach(line);

    win.wait_for_button();       // give control to the display engine
}