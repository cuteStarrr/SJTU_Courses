#include "BarChart.h"

void BarChart::DrawBar(Point o, Color col, Simple_window & window) {
    Point left_bottum(o.x + start, o.y);
    for(int i = 0; i < data.size(); ++i) {
        int hight = round(scale * data[i]);
        Point left_top(left_bottum.x, left_bottum.y - hight);

        bars.add(left_bottum);
        bars.add(left_top);
        bars.add(Point(left_top.x + width, left_top.y));
        bars.add(Point(left_bottum.x + width, left_bottum.y));
        

        //Text temp(Point(left_top.x, left_top.y - 5), to_string(data[i]));

        //window.attach(temp);

        left_bottum.x += dist;
    }

    bars.set_fill_color(col);
    window.attach(bars);
}