#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <sstream>
#include <iomanip>

using namespace std;


class Polynomial
{
    public:
    float coef[50] = {0}; //最大指数的范围，可调节
    int highest_index = 0;

    public:
    Polynomial(string str);
    Polynomial() {};
    Polynomial(const Polynomial& obj) {
        highest_index = obj.highest_index;
        for(int i = 0; i <= highest_index; ++i) {
            coef[i] = obj.coef[i];
        }
    }
    Polynomial Divide(Polynomial divisor, Polynomial& remainder);
};

Polynomial Polynomial::Divide(Polynomial divisor, Polynomial& remainder) {
    Polynomial ans;
    remainder = *this;
    int tmp_index;
    if(highest_index < divisor.highest_index) {
        remainder = *this;
        return ans;
    }
    else {
        ans.highest_index = highest_index - divisor.highest_index;
        for(int i = 0; i <= ans.highest_index; ++i) {
            ans.coef[ans.highest_index - i] = remainder.coef[remainder.highest_index - i] / divisor.coef[divisor.highest_index];
            for(int j = 0; j <= divisor.highest_index; ++j) {
                remainder.coef[remainder.highest_index - j - i] = remainder.coef[remainder.highest_index - j - i] - ans.coef[ans.highest_index - i] * divisor.coef[divisor.highest_index - j];
            }
        }
        tmp_index = divisor.highest_index - 1;
        while(remainder.coef[tmp_index] == 0) --tmp_index;
        remainder.highest_index = tmp_index;
    }
    return ans;
}

Polynomial::Polynomial(string str) {
    string last = ""; //coef
    string index = "";
    int sub_flag = 0;
    int num_flag = 0;
    int x_flag = 0;
    int index_flag = 0;
    int correct_flag = 0;
    int pos = 0;
    int size = str.size();
    int value;
    int max_index = 0;
    while(pos <= size) {
        if(pos < size) value = int(str[pos]);
        else value = -1; //结束
        if(value >= 48 && value <= 57 || value == 46) {  // 为数字
            last = last + str[pos];
            num_flag = 1;
            ++pos;
            continue;
        }

        if(value == 120) { //x
            x_flag = 1;
            ++pos;
            continue;
        }
        
        if (value == 94) { // ^, index
            ++pos;
            int index_value;
            while(pos < size) {
                index_value = int(str[pos]);
                if (index_value >= 48 && index_value <= 57) {
                    index = index + str[pos];
                    ++pos;
                    index_flag = 1;
                }
                else break;
            }
            continue;
        }

        if(value == 43 || value == 45 || value == -1) { // +,-,finish
            if(num_flag) {
                if(index_flag && x_flag) {
                    coef[atoi(index.c_str())] = coef[atoi(index.c_str())] + pow(-1,sub_flag) * atof(last.c_str()); correct_flag = 1;
                    if(atoi(index.c_str()) > max_index) max_index = atoi(index.c_str());
                }
                if(x_flag && !(index_flag)) {
                    coef[1] = coef[1] + pow(-1,sub_flag) * atof(last.c_str()); correct_flag = 1;
                    if(1 > max_index) max_index = 1;
                }
                if(!(x_flag) && !(index_flag)) {coef[0] = coef[0] + pow(-1,sub_flag) * atof(last.c_str()); correct_flag = 1;}
            }
            else {
                if(index_flag && x_flag) {
                    coef[atoi(index.c_str())] = coef[atoi(index.c_str())] + pow(-1,sub_flag) * 1; correct_flag = 1;
                    if(atoi(index.c_str()) > max_index) max_index = atoi(index.c_str());
                }
                if(x_flag && !(index_flag)) {
                    coef[1] = coef[1] + pow(-1,sub_flag) * 1; correct_flag = 1;
                    if(1 > max_index) max_index = 1;
                }
                if(!(x_flag) && !(index_flag)) {correct_flag = 1;}
            }

            if(correct_flag) {
                index = "";
                last = "";
                if(value == 43) sub_flag = 0;
                else sub_flag = 1;
                num_flag = 0;
                x_flag = 0;
                index_flag = 0;
                correct_flag = 0;
                ++pos;
                continue;
            }
            else {
                cerr << "not a polynomial!" << endl;
            }
        }

        cerr << "not a polynomial!" << endl;

    }

    highest_index = max_index;

}

string Get_Outstring (Polynomial src) {
    string total = "";
    string str = "";
    int add_flag = 0;

    for(int i = src.highest_index; i >= 0; --i) {
        if(src.coef[i] != 0) {
            add_flag = src.coef[i] > 0 ? 1 : 0;
            ostringstream out;
            out << src.coef[i];
            str = out.str();
            size_t n=str.find('.');
            if(n != str.npos) {// 有小数点
                int need_len = (4 - (str.size() - n - 1)) > 0 ? (4 - (str.size() - n - 1)) : 0;
                if(need_len) {
                    for(int k = need_len; k > 0 ; --k) {
                        str = str + "0";
                    }
                }
                else {
                    str[n + 5] = '\0';
                }
            }
            else {str = str + ".0000";}

            if(i >= 2) {
                str = str + "x^" + to_string(i);
            }
            else {
                if(i == 1) {
                    str = str + "x";
                }
            }
            if(add_flag) {
                if(i < src.highest_index)
                    total = total + "+" + str;
                else total = total + str;
            }
            else {total = total + str;}
        }
    }
    return total;
}


int main() {

    string str;
    int in_char = 1;
    int out_char = 3;

    //getline(cin,str);
    str = "-5x-1+2x^2";
    Polynomial divided(str);
    in_char = in_char + str.size();

    //getline(cin,str);
    str = "x-3";
    Polynomial divisor(str);
    in_char = in_char + str.size();

    Polynomial answer;
    Polynomial rest;
    
    answer = divided.Divide(divisor, rest);

    string out_string1 = Get_Outstring(divided);
    out_char += out_string1.size();
    string out_string2 = Get_Outstring(divisor);
    out_char += out_string2.size();
    string out_string3 = Get_Outstring(answer);
    out_char += out_string3.size();
    string out_string4 = Get_Outstring(rest);
    out_char += out_string4.size();

    cout << in_char << ':' << out_char << '\n';
    cout << out_string1 << '\n';
    cout << out_string2 << '\n';
    cout << out_string3 << '\n';
    cout << out_string4;

    return 0;
}