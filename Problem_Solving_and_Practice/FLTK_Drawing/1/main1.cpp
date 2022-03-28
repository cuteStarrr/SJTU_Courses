
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "BarChart.h"

//------------------------------------------------------------------------------

void GetAverageTemp(string file, vector<double> & temp) {
    ifstream fp(file, ios::in);
    if(!fp) {
        cout << "Can't open file: " << file << '!';
        exit(1);
    }

    string line;
    getline(fp,line);
    int month = 1;
    int day = 0;
    double sum = 0;
    while(getline(fp,line)) {
        string time;
        string temprature;
        istringstream data(line);
        getline(data, time, ',');
        getline(data, temprature, ',');

        istringstream which_month(time);
        string m;
        getline(which_month, m, '/');
        getline(which_month, m, '/');
        if(atoi(m.c_str()) == month) {
            sum += atof(temprature.c_str());
            ++day;
            if(month == 12 && day == 31) temp.push_back(sum / day);
        }
        else {
            temp.push_back(sum / day);
            ++month;
            day = 1;
            sum = atof(temprature.c_str());
        }
    }
}

//------------------------------------------------------------------------------

int main()
{
    vector<double> temp_austin;
    vector<double> temp_newyork;
    GetAverageTemp("/home/littlestar/Documents/Codes/Cpp/Cpp_Multiple/fltk/FLTK2/1/Austin.csv", temp_austin);
    GetAverageTemp("/home/littlestar/Documents/Codes/Cpp/Cpp_Multiple/fltk/FLTK2/1/NewYork.csv", temp_newyork);

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl,1280,360,"Canvas");    // make a simple window
    // axis x: each month occupies 40 pixels, and each bar occupies 10 pixels.
    // axis y: 80 pixels to denote the temprature
    // we assume the max temp is 40, so the hight of temp draw in the window is round(t * 2)
    // there are 20 pixels space to the side
    Point orig(60, 300);

    Axis month(Axis::x, orig, 1040, 13, "Month");
    Axis temp(Axis::y, orig, 240, 40, "Temprature(C)");

    Lines grid;
    for(int x = 140; x < 1101; x += 80) grid.add(Point(x, orig.y), Point(x, 60));
    for(int y = 60; y < 300; y += 6) grid.add(Point(orig.x, y), Point(1100, y));

    win.attach(grid);
    win.attach(month);
    win.attach(temp);

    BarChart austin(60, 20, 6, 80, temp_austin);
    BarChart newyork(80, 20, 6, 80, temp_newyork);

    austin.DrawBar(orig, Color::red, win);
    newyork.DrawBar(orig, Color::blue, win);

    Text title(Point(300, 30), "The Average month temprature of Austin and New York");
    title.set_font_size(20);
    Text x_label(Point(1080, orig.y + 15), "month");
    x_label.set_font_size(15);
    Text y_label(Point(20, 50), "temprature(C)");
    y_label.set_font_size(15);

    Text m1(Point(120 + 15, orig.y + 15), "1");
    m1.set_font_size(12);
    Text m2(Point(200 + 15, orig.y + 15), "2");
    m2.set_font_size(12);
    Text m3(Point(280 + 15, orig.y + 15), "3");
    m3.set_font_size(12);
    Text m4(Point(360 + 15, orig.y + 15), "4");
    m4.set_font_size(12);
    Text m5(Point(440 + 15, orig.y + 15), "5");
    m5.set_font_size(12);
    Text m6(Point(520 + 15, orig.y + 15), "6");
    m6.set_font_size(12);
    Text m7(Point(600 + 15, orig.y + 15), "7");
    m7.set_font_size(12);
    Text m8(Point(680 + 15, orig.y + 15), "8");
    m8.set_font_size(12);
    Text m9(Point(760 + 15, orig.y + 15), "9");
    m9.set_font_size(12);
    Text m10(Point(840 + 15, orig.y + 15), "10");
    m10.set_font_size(12);
    Text m11(Point(920 + 15, orig.y + 15), "11");
    m11.set_font_size(12);
    Text m12(Point(1000 + 15, orig.y + 15), "12");
    m12.set_font_size(12);

    Text t1(Point(50, orig.y + 5), "0");
    t1.set_font_size(12);
    Text t2(Point(43, orig.y + 5 - 60), "10");
    t2.set_font_size(12);
    Text t3(Point(43, orig.y + 5 - 120), "20");
    t3.set_font_size(12);
    Text t4(Point(43, orig.y + 5 - 180), "30");
    t4.set_font_size(12);
    Text t5(Point(43, orig.y + 5 - 240), "40");
    t5.set_font_size(12);

    win.attach(t1);
    win.attach(t2);
    win.attach(t3);
    win.attach(t4);
    win.attach(t5);

    win.attach(m1);
    win.attach(m2);
    win.attach(m3);
    win.attach(m4);
    win.attach(m5);
    win.attach(m6);
    win.attach(m7);
    win.attach(m8);
    win.attach(m9);
    win.attach(m10);
    win.attach(m11);
    win.attach(m12);

    Rectangle lg1(Point(1150, 60), 20, 15);
    lg1.set_fill_color(Color::red);
    Text city1(Point(1180, 72), "Austin");
    city1.set_font_size(14);
    Rectangle lg2(Point(1150, 80), 20, 15);
    lg2.set_fill_color(Color::blue);
    Text city2(Point(1180, 92), "New York");
    city2.set_font_size(14);

    win.attach(lg1);
    win.attach(city1);
    win.attach(lg2);
    win.attach(city2);

    win.attach(title);
    win.attach(x_label);
    win.attach(y_label);
    win.wait_for_button();       // give control to the display engine

    return 0;
}

//------------------------------------------------------------------------------
