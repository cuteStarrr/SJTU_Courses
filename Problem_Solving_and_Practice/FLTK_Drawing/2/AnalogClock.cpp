#include "AnalogClock.h"

void AnalogClock::ShowTime(Simple_window & win) {
    Out_box time_out(Point(430,100), 150, 20, "Current time:");
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
}