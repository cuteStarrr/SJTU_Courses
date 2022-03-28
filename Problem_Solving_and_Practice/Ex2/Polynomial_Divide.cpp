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
    private:
    float coef[50] = {0}; //最大指数的范围，可调节
    int highest_index = 0;
    int isLegal = 1;

    public:
    Polynomial(string str);
    Polynomial() {
        for(int i = 0; i < 50; ++i) coef[i] = 0;
        highest_index = 0;
        isLegal = 1;
    };
    Polynomial(const Polynomial& obj) {
        highest_index = obj.highest_index;
        for(int i = 0; i <= highest_index; ++i) {
            coef[i] = obj.coef[i];
        }
        isLegal = obj.isLegal;
    }
    Polynomial Divide(Polynomial divisor, Polynomial& remainder);
    void Get_Outstring (string & str);
    bool isCorrectInput(Polynomial divisor); // divided调用
};

bool Polynomial::isCorrectInput(Polynomial divisor) {
    if(isLegal && divisor.isLegal) {
        if(divisor.highest_index == 0 && divisor.coef[0] == 0) return false;
        return true;
    }
    return false;
}

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
        if(tmp_index >= 0) remainder.highest_index = tmp_index;
        else remainder.highest_index = 0;
    }
    return ans;
}

Polynomial::Polynomial(string str) {
    string last = ""; //coef
    string index = "";
    int symbol_flag = 0;
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
            symbol_flag = 0;
            ++pos;
            continue;
        }

        if(value == 120) { //x
            x_flag = 1;
            symbol_flag = 0;
            ++pos;
            continue;
        }
        
        if (value == 94) { // ^, index
            ++pos;
            symbol_flag = 0;
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
            if(symbol_flag) {
                isLegal = 0;
                break;
            }
            symbol_flag = 1;
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
                isLegal = 0;
                break;
            }
        }

        isLegal = 0;
        break;

    }

    highest_index = max_index;

}

void Polynomial::Get_Outstring (string & output) {
    string total = "";
    string str = "";
    int add_flag = 0;

    for(int i = highest_index; i >= 0; --i) {
        if(coef[i] != 0) {
            add_flag = coef[i] > 0 ? 1 : 0;
            ostringstream out;
            out << coef[i];
            str = out.str();
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

            if(i >= 2) {
                str = str + "x^" + to_string(i);
            }
            else {
                if(i == 1) {
                    str = str + "x";
                }
            }
            if(i != highest_index) {
                if(add_flag) {
                    total = total + '+' + str;
                }
                else {total = total + str;}
            }
            else total = total + str;
        }
        else {
            if(i == highest_index) {
                total = "0.0000";
            }
        }
    }
    output = total;
}

int main() 
{
    //第二关执行代码

    string str1;
    string str2;
    int in_char = 1;
    int out_char = 3;

    //getline(cin,str1);
    Polynomial divided("5-6x");
    in_char = in_char + str1.size();

    //getline(cin,str2);
    Polynomial divisor("1+-x");
    in_char = in_char + str2.size();

    //!divided.isCorrectInput(divisor)
    
    if(!divided.isCorrectInput(divisor)) {
        cout << in_char << ':' << 23 << '\n';
        cout << "error" << '\n';
        cout << "error" << '\n';
        cout << "error" << '\n';
        cout << "error";

        return 0;
    }

    Polynomial answer;
    Polynomial rest;
    
    answer = divided.Divide(divisor, rest);

    string out_string1;
    divided.Get_Outstring(out_string1);
    string out_string2;
    divisor.Get_Outstring(out_string2);
    string out_string3;
    answer.Get_Outstring(out_string3);
    string out_string4;
    rest.Get_Outstring(out_string4);

    out_char += out_string1.size();
    out_char += out_string2.size();
    out_char += out_string3.size();
    out_char += out_string4.size();

    cout << in_char << ':' << out_char << '\n';
    cout << out_string1 << '\n';
    cout << out_string2 << '\n';
    cout << out_string3 << '\n';
    cout << out_string4;
    
  	return 0;
}