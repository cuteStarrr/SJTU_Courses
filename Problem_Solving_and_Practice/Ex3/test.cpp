#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>
#include <time.h>
#include <sstream>

using namespace std;

#define MAXNUM 50

class LinearEquations
{
    private:
    string symbol[MAXNUM];
    double matrix[MAXNUM][MAXNUM] = {0};
    int symbol_num = 0;
    int equation_num = 0;
    double answer[MAXNUM] = {0};
    int error1 = 0;
    int error2 = 0;
    int RA = 0;
    int RB = 0;
    int limit = 0;

    public:
    LinearEquations() : symbol_num(0), equation_num(0), error1(0), error2(0), RA(0), RB(0), limit(0) {
        for(int i = 0; i < MAXNUM; ++i) {
            symbol[i] = "";
        }
        for(int i = 0; i < MAXNUM; ++i) {
            for(int j = 0; j < MAXNUM; ++j) 
                matrix[i][j] = 0;
        }
    }

    LinearEquations(string * var, double val[][MAXNUM], int var_num, int line) {
        for(int i = 1; i <= var_num; ++i) {
            symbol[i] = var[i];
        }
        for(int i = 1; i <= line; ++i) {
            for(int j = 0; j <= var_num; ++j) 
                matrix[i][j] = val[i][j];
        }
        symbol_num = var_num;
        equation_num = line;
    }

    LinearEquations(const LinearEquations& obj) {
        symbol_num = obj.symbol_num;
        equation_num = obj.equation_num;
        error1 = obj.error1;
        error2 = obj.error2;
        RA = obj.RA;
        RB = obj.RB;
        limit = obj.limit;
        for(int i = 1; i <= symbol_num; ++i) {
            symbol[i] = obj.symbol[i];
        }
        for(int i = 1; i <= equation_num; ++i) {
            for(int j = 0; j <= symbol_num; ++j) 
                matrix[i][j] = obj.matrix[i][j];
        }
    }

    void SimplifyMatrix();
    bool FindAnswer();
    string OutputAnswer();
    string FloatStr(double num);
    void Print();
};

void LinearEquations::Print() {
    cout << "\nsymbols:\n" ;
    for(int i = 1; i <= symbol_num; ++i)
        cout << symbol[i] << ' ';
    cout << "\nmatrix:\n" ;
    for(int i = 1; i <= equation_num; ++i) {
        for(int j = 0; j <= symbol_num; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

string LinearEquations::FloatStr(double num) {
    ostringstream streamflow;
    streamflow << num;
    string str = streamflow.str();
    size_t n=str.find('.');
    if(n != str.npos) {// 有小数点
        int need_len;
        if(5 + n > str.size()) {
            need_len = 5 + n - str.size();
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

string LinearEquations::OutputAnswer() {
    SimplifyMatrix();
    int ans_flag = FindAnswer();
    if(!ans_flag) {
        if(error1) return "error1\n";
        else return "error2\n";
    }

    string output = "";
    for(int i = 1; i <= symbol_num; ++i) {
        output = output + symbol[i] + ":" + FloatStr(matrix[i][0]) + "\n";
    }

    return output;
}

bool LinearEquations::FindAnswer() {
    int find_RA = 0;
    while(limit >= 1) {
        for(int i = 1; i <= symbol_num; ++i) {
            if(abs(matrix[limit][i]) > 0.00001) {
                RA = limit;
                find_RA = 1;
                break;
            }
        }
        if(!find_RA) {
            --limit;
        }
        else break;
    }
    if(matrix[RA + 1][0]) {error1 = 1; return false;}
    else {
        if(symbol_num > RA) {error2 = 1; return false;}
        else if(symbol_num == RA) return true;
    }

    return false;
}

void LinearEquations::SimplifyMatrix() {
    int row = 1;
    int line = 1;
    int finish = 0;
    Print();
    while(!finish) {
        while(abs(matrix[row][line]) < 0.00001) {
            int change_row = 0;
            for(int i = row + 1; i <= equation_num; ++i) {
                if(abs(matrix[i][line]) > 0.00001) {
                    change_row = 1;
                    int tmp;
                    for(int j = 0; j <= symbol_num; ++j) {
                        tmp = matrix[row][j];
                        matrix[row][j] = matrix[i][j];
                        matrix[i][j] = tmp;
                    }
                    break;
                }
            }
            if(!change_row) {
                if(line < symbol_num) {
                    ++line;
                    continue;
                }
                else {
                    finish = 1;
                    limit = row - 1;
                    break;
                }
            }
        }
        if(!finish) {
            if(abs(matrix[row][line] - 1) > 0.00001) {
                double tmp = matrix[row][line];
                for(int i = 0; i <= symbol_num; ++i) {
                    if(abs(matrix[row][i]) > 0.00001) {
                        matrix[row][i] = matrix[row][i] / tmp;
                        cout << matrix[row][i] << endl;
                    }
                }
            }
            for(int i = 1; i <= equation_num; ++i) {
                if(i != row) {
                    double time = matrix[i][line] * (-1);
                    for(int j = 0; j <= symbol_num; ++j) {
                        matrix[i][j] = matrix[i][j] + time * matrix[row][j];
                        cout << matrix[i][j] << endl;
                    }
                }
            }
            if(row == equation_num || line == symbol_num) {finish = 1; limit = row;}
            else {++row; ++line;}
            Print();
        }
    }
}

class Term {  //表示每一项 eg. 5x1
    public:
    double value;
    string variable;
    Term() : value(0), variable("") {}
    Term(string str) : value(1), variable(str) {}
    Term(double num, string str) : value(num), variable(str) {}

};

/*
class IllegalEquation {
    private:
    string illegal_equation = "";

    public:
    IllegalEquation(): illegal_equation("") {}
    IllegalEquation(string str): illegal_equation(str) {}
    string GetIllegal() {
        return illegal_equation;
    }

};
*/

float GetFloat(string str, int & pos) {
    int ch = int(str[pos]);
    string tmp = "";
    double value;

    while((ch >= 48 && ch <= 57) || ch == 46 || ch == 45) {
        tmp = tmp + str[pos];
        ++pos;
        if(pos == str.size()) break;
        ch = int(str[pos]);
    }
    value = atof(tmp.c_str());
    return value;
}

string GetString(string str, int & pos) {
    string variable = "";

    variable = variable + str[pos];
    ++pos;
    int ch = int(str[pos]);
    while(ch >= 48 && ch <= 57) {
        variable = variable + str[pos];
        ++pos;
        if(pos == str.size()) break;
        ch = int(str[pos]);
    }
    return variable;
}

Term LetterTerm(string str, int & pos) {
    string var;
    double val;
    var = GetString(str, pos); // pos变为接下来要处理的字符的位置
    val = 1;
    return Term(val, var);
}

Term NumTerm(string str, int & pos) {
    string var;
    double val;
    val = GetFloat(str, pos);
    if(str[pos] != '*') throw str; // 跳过*
    ++pos;
    int ch = int(str[pos]);
    if(ch >= 97 && ch <= 122) { // 字母开头
        var = GetString(str, pos); // pos变为接下来要处理的字符的位置
    }
    else throw str;
    return Term(val, var);
}

Term OpTerm(string str, int & pos, bool add) {
    
    int ch = int(str[pos]);
    if(ch >= 48 && ch <= 57) {
        Term tmp = NumTerm(str, pos);
        if(!add) tmp.value = tmp.value * (-1);
            return tmp;
    }
    if(ch >= 97 && ch <= 122) {
        Term tmp = LetterTerm(str, pos);
        if(!add) tmp.value = tmp.value * (-1);
            return tmp;
    }

    throw str;
}

Term GetTerm(string str, int & pos) {
    string variable = "";

    int ch = int(str[pos]);

    if(ch >= 97 && ch <= 122) { // 字母开头
        return LetterTerm(str, pos);
    }

    if(ch >= 48 && ch <= 57) { // 数字开头
        return NumTerm(str, pos);
    }

    if(ch == 43 || ch == 45) { // + - 开头
        ++pos;
        bool add = !(ch - 43);
        return OpTerm(str, pos, add);
    }

    throw str;
}


string GetMatrix(int & variable_num, int & line, string* variables, double coef[][MAXNUM], int & in_num, string & legal) {
    string str_total[3] = {"x0+2*y1+3*z2=5","3*x0-y1+2*z2=8","x0+y1+2*z2=2"};
    string illegal = "";

    int cur = 0;

    while(cur < 3) {
        string str = str_total[cur];
        ++cur;
        ++line;
        int size = str.size();
        if(size == 0) break;

        in_num = in_num + size + 1;
        
        try {
            int equal_pos = str.find('=');
            if(equal_pos == string::npos) throw -1;
            else {
                ++equal_pos; // 跳过=
                int tmp = GetFloat(str,equal_pos);
                if(equal_pos < size) throw -1;
            }
            int pos = 0;
            while(str[pos] != '=') {
                Term term = GetTerm(str, pos); // 此时pos的位置是接下来要处理的字符
                int flag = 1;
                for(int i = 1; i <= variable_num; ++i) {
                    if(term.variable == variables[i]) {
                        coef[line][i] = term.value;
                        flag = 0;
                    }
                }
                if(flag) {
                    ++variable_num;
                    variables[variable_num] = term.variable;
                    coef[line][variable_num] = term.value;
                }
            }
            ++pos; // 跳过=
            coef[line][0] = GetFloat(str,pos);
            legal = legal + str + "\n";
        } catch(int) {
            --line;
            illegal = illegal + "\n" + str;
        }
        catch(...) {
            cout << "catch it!" << endl;
        }
    }

    return illegal;
}


int main() {
    int variable_num = 0;
    int line = 0;
    string str;
    string variables[MAXNUM];
    double coef[MAXNUM][MAXNUM] = {0}; // 从第一行开始写矩阵，从第一列开始表示系数，第0列表示等式右边的常数
    
    string illegal_equations = ""; // '\n' + str
    int input_char = 0;
    string legal_equations = "Legal Equations:\n";  // str + '\n'
    int output_char = 0;

    illegal_equations = GetMatrix(variable_num, line, variables, coef, input_char, legal_equations);
    illegal_equations = "Illegal Equations:" + illegal_equations;
    --input_char;

    LinearEquations equations(variables, coef, variable_num, line);

    string answer = equations.OutputAnswer();

    output_char = legal_equations.size() + answer.size() + illegal_equations.size();
    
    cout << input_char << ':' << output_char << '\n';
    cout << legal_equations;
    cout << answer;
    cout << illegal_equations;

    equations.Print();

    return 0;
}