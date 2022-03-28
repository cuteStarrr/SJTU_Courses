#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>
#include <time.h>
#include <sstream>
#include <map>

using namespace std;

bool Get_Value(string str, long double & num) {
    for(int i = 0; i < str.size(); ++i) {
        int value = int(str[i]);
        if(!((value >= 48 && value <= 57) || value == 46 || value == 43 || value == 45)) {
            cout << "error";
            return false;
        }
    }
    num = strtold(str.c_str(), NULL);
    return true;
}

string Point_four(long double num) {
    string str = to_string(num);
    size_t n=str.find('.');
    if(n != str.npos) {// 有小数点
        int need_len;
        if(5 + n > str.size()) {
            need_len = 4 - str.size() + n + 1;
        }
        else need_len = 0;
        if(need_len) {
            for(int k = need_len; k > 0 ; --k) {
                str = str + "0";
            }
        }
        else {
            str = str.substr(0,n + 5);
        }
    }
    else {str = str + ".0000";}

    return str;
}

int main(){
        long double x;
        long double sum_x = 0;
        long double sum_y = 0;
        long double sum_xy = 0;
        long double sum_x2 = 0;
        long double sum_y2 = 0;
        map<long double, long double> points;
        string str;
        getline(cin,str);
        if(!(Get_Value(str, x))) {
            cout << "error" << '\n';
            cout << "error";
            return 0;
        }
        //cout << x << '\n';
        while(getline(cin,str)) {
            //cout << '@' << '\n';
            long double tmp_x, tmp_y;
            string out;
            istringstream s(str);
            s >> out;
            if(!(Get_Value(out, tmp_x))) {
                cout << "error" << '\n';
                cout << "error";
                return 0;
            }
            sum_x += tmp_x;
            sum_x2 += tmp_x * tmp_x;
            //cout << tmp_x << '\n';
            s >> out;
            if(!(Get_Value(out, tmp_y))) {
                cout << "error" << '\n';
                cout << "error";
                return 0;
            }
            sum_y += tmp_y;
            sum_xy += tmp_x * tmp_y;
            sum_y2 += tmp_y * tmp_y;
            //cout << tmp_y << '\n';
            points.insert(pair<long double, long double>(tmp_x, tmp_y));
        }
        int n = points.size();
        long double x_hat = sum_x / n;
        long double y_hat = sum_y / n;
        long double r = (sum_xy - n * x_hat * y_hat) / pow((sum_x2 - n * x_hat * x_hat) * (sum_y2 - n * y_hat * y_hat), 0.5);

        if(0.75 - abs(r) > 0.00001) {
            cout << Point_four(r) << '\n';
            cout << "error" << '\n';
            cout << "error";
            return 0;
        }
        
        long double k = (sum_xy - n * x_hat * y_hat) / (sum_x2 - n * x_hat * x_hat);
        long double b = y_hat - k * x_hat;

        cout << Point_four(r) << '\n';
        cout << "y=" << Point_four(k) << "*x+" << Point_four(b) << '\n';
        cout << Point_four(k * x + b);

    return 0;
}