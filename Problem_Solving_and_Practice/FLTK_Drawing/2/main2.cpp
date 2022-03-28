
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "AnalogClock.h"

//------------------------------------------------------------------------------

int main()
{

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl,600,400,"Canvas");    // make a simple window

    AnalogClock time_clock(Point(200, 200), 100, 2, win);

    time_clock.ShowTime(win);

/*
    Circle clock(Point(200,200), 100);
    Circle orig(Point(200,200), 2);
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

    Out_box time_out(Point(450,100), 150, 20, "Current time:");
    win.attach(time_out);

    win.show();

    while(true){
        time_t time_seconds = time(0);
        struct tm now_time;
        localtime_r(&time_seconds, &now_time);

        int year = now_time.tm_year + 1900;
        int month = now_time.tm_mon + 1;
        int day = now_time.tm_mday;
        int hour = now_time.tm_hour;
        int minute = now_time.tm_min;
        int second = now_time.tm_sec;

        stringstream ss;
        ss << year << '/' << month << '/' << day << ' ' << hour << ':' << minute;
        time_out.put(ss.str());

        Line h(Point(200,200), Point(int(200 + 30 * sin((30 * hour + minute / 2) * 3.14159 / 180)), int(200 - 30 * cos((30 * hour + minute / 2) * 3.14159 / 180))));
        Line m(Point(200,200), Point(int(200 + 60 * sin((6 * minute) * 3.14159 / 180)), int(200 - 60 * cos((6 * minute) * 3.14159 / 180))));
        Line s(Point(200,200), Point(int(200 + 90 * sin((6 * second) * 3.14159 / 180)), int(200 - 90 * cos((6 * second) * 3.14159 / 180))));
        win.attach(h);
        win.attach(m);
        win.attach(s);
        Fl::wait(1);
        Fl::redraw();
    }
*/

    win.wait_for_button();       // give control to the display engine
}

//------------------------------------------------------------------------------
