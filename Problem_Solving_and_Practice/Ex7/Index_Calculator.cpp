//
// This is example code from Chapter 7.7 "Recovering from errors" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "std_lib_facilities.h"
#include<map>
#include<set>

int in_char = 0;
int out_char = 0;
stringstream ss;
int bad_input = 0;
map<string, vector<string>> index_exp;


/*
    Simple calculator

    Revision history:

        Revised by Bjarne Stroustrup May 2007
        Revised by Bjarne Stroustrup August 2006
        Revised by Bjarne Stroustrup August 2004
        Originally written by Bjarne Stroustrup
            (bs@cs.tamu.edu) Spring 2004.

    This program implements a basic expression calculator.
    Input from cin; output to cout.

    The grammar for input is:

    Statement:
        Expression
        Print
        Quit

    Print:
        ;

    Quit:
        q

    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal


        Input comes from cin through the Token_stream called ts.
*/

//------------------------------------------------------------------------------

const char number = '8';    // t.kind==number means that t is a number Token
const char quit   = 'q';    // t.kind==quit means that t is a quit Token
const char print  = ';';    // t.kind==print means that t is a print Token
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result

//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    void Clear_buffer();
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
    void ignore(char c);      // discard tokens up to an including a c
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------
void Token_stream::Clear_buffer() {
    full = false;
    buffer = 0;
    return ;
}



// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get() // read characters from cin and compose a Token
{
    if (full) {         // check if we already have a Token ready
        full=false;
        //cout << "it gets from buffer " << "kind: " << buffer.kind << " value " << buffer.value << '\n';
        return buffer;
    }

    char ch;
    ss >> ch;
    while(ch == ' ') ss >> ch;

    switch (ch) {
    case quit:
    case print:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '!':
        {
            return Token(ch); // let each character represent itself
        }
    case '.':             // a floating-point literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':    // numeric literal
    {
        //string last = "";
        //while(int(ch) >= 48 && int(ch) <= 57 || int(ch) == 46) {
        //    last += ch;
        //    ss >> ch;
        //}
        ss.putback(ch);// put digit back into the input stream
        double val;
        ss >> val;     // read a floating-point number
        //val = atof(last.c_str());
        //cout << "the number is: " << val << '\n';
        return Token(number,val);
    }
    default:
        //cout << "the bad token is " << int(ch) << '\n';
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
    // c represents the kind of a Token
{
    // first look in buffer:
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now seach input:
    char ch = 0;
    while (ss>>ch) {
        if (ch==c) return;
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    //++count_time;
    Token t = ts.get();
    switch (t.kind) {
    case '(':           // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            Token next = ts.get();
            if (next.kind == '!') {
                if (d > 0) {
                    if (ceil(d) == floor(d)) {
                        int tmp = d;
                        int res = 1;
                        while(tmp > 0) {
                            res = res * tmp;
                            --tmp;
                        }
                        return res; 
                    }
                    else error("!: invalid factorial");
                }
                if (abs(d) < 0.00001) {
                    return 1;
                }
                error("!: invalid factorial");
            }
            else {
                ts.putback(next);
                return d;
            }
        }
    case number:
        {
            Token next = ts.get();
            //cout << "the next token in primary of number " << next.kind << " " << next.value << '\n';
            if (next.kind == '!') {
                if (t.value > 0) {
                    if (ceil(t.value) == floor(t.value)) {
                        int tmp = t.value;
                        int res = 1;
                        while(tmp > 0) {
                            res = res * tmp;
                            --tmp;
                        }
                        //cout << "the times: " << count_time << " ! :" << res << '\n';
                        return res; 
                    }
                    else error("!: invalid factorial");
                }
                if (abs(t.value) < 0.00001) {
                    return 1;
                }
                error("!: invalid factorial");
            }
            else {
                ts.putback(next);
                return t.value;    // return the number's value
            }
        }
    case '-':
        return - primary();
    case '+':
        return primary();
    default:
        //cout << "what is now:" << t.kind << '\n';
        error("primary need");
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    //cout << "left " << left <<'\n';
    Token t = ts.get(); // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
            {
                double d = 10;
                d = primary();
                //if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        case '%':
            {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(term());
                if (i2 == 0) error("%: divide by zero");
                left = i1%i2;
                t = ts.get();
                break;
            }
        default:
            ts.putback(t);        // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

void calculate()
{
    stringstream output;
    while (ss)
      try {
        output.clear();
        output << prompt;
        Token t = ts.get();
        while (t.kind == print) {
            //++in_char;
            t=ts.get();    // first discard all "prints"
        }
        if (t.kind == quit) {
            //++in_char;
            string out_string = output.str();
            cout << in_char << ':' << out_string.size() << '\n';
            cout << output.str();
            return;        // quit
        }
        ts.putback(t);
        output << result << expression() << '\n';
        //cout << result << expression() << endl;
    }
    catch (exception& e) {
        output << e.what() << endl;        // write error message
        clean_up_mess();
    }
}

//------------------------------------------------------------------------------

int main()
try {
    char c;
    string line1;
    string line2;
    getline(cin,line1);
    line1 = line1 + "\n";
    getline(cin,line2);
    stringstream flow;
    flow.str(line1);
    c = flow.get();

    // 对输入索引进行检查，去掉空格
    int cur = 0;
    while(line2[cur] == ' ') ++cur;
    line2 = line2.substr(cur);
    cur = line2.size() - 1;
    while(line2[cur] == ' ') {
        --cur;
    }
    line2 = line2.substr(0, cur + 1);

    while(c != '\n' || c != EOF) { //每个索引一个开头
        while(c == ' ') c = flow.get(); // 跳过空格
        string index = "";
        string exp = "";
        string tmp = "";
        int exist_flag = 0;
        string block = ""; // 记录空格
        if(c == 'q' || c == '\n') break;
        if(c == '[') { // 开始索引
            c = flow.get();
            while(c == ' ') c = flow.get(); // 跳过开始的空格
            while(c != ']') { // 得到索引的一部分
                tmp += c;
                c = flow.get();
            }
            int pos = tmp.size() - 1;
            while(tmp[pos] == ' ') {
                --pos;
            }
            index = tmp.substr(0, pos + 1);
            map<string, vector<string>> :: iterator it;
            it = index_exp.find(index);
            if(it != index_exp.end()) { // 此索引已存在
                exist_flag = 1;
            }
            tmp = "";
            c = flow.get();
            while(c == ' ') c = flow.get();
            while(c != ';') {
                if(c != '\n') {
                    tmp += c;
                    c = flow.get();
                }
                else {
                    flow.putback(c);
                    break;
                }
            }
            //tmp += ';';
            //tmp.erase(remove(tmp.begin(), tmp.end(), ' '), tmp.end());
            pos = tmp.size() - 1;
            while(tmp[pos] == ' ') {
                --pos;
            }
            exp = tmp.substr(0, pos + 1);
            //exp = tmp; // 得到索引对应的表达式
            if(exist_flag) { // 索引存在时
                vector<string> exps = it -> second;
                exps.push_back(exp);
                index_exp.erase(it);
                index_exp.insert(pair<string, vector<string>> (index, exps));
            }
            else {
                vector<string> exps;
                exps.push_back(exp);
                index_exp.insert(pair<string, vector<string>> (index, exps));
            }
        }
        else {
            if(line2.size() > 0) {
                cout << '[' << line2 << ']';
                return 0;
            }
            else {
                map<string, vector<string>> :: iterator maps = index_exp.begin();
                for(; maps != index_exp.end(); ++maps) {
                    cout << '[' << maps -> first << ']';
                }
                return 0;
            }
        }
        c = flow.get();
    }
    if(line2.size() > 0) { // 有索引输入
        map<string, vector<string>> :: iterator iter;
        iter = index_exp.find(line2);
        cout << '[' << line2 << ']';
        if(iter == index_exp.end()) { // 此索引不存在
            return 0;
        }
        else { // 索引存在
            vector<string> exps = iter -> second;
            sort(exps.begin(), exps.end());
            vector<string> :: iterator itexp = exps.begin();
            for(; itexp != exps.end(); ++itexp) {
                ss.clear();
                ss.str(*itexp + ";");
                ts.Clear_buffer();
                //cout << "the flow is " << ss.str() << '\n';
                double ans;
                try{
                    ans = expression();
                }
                catch (runtime_error& e) {
                    bad_input = 1;
                    //cout << e.what() << endl;
                }
                if(!bad_input) {
                    cout << '\n' << *itexp << '=' << ans;
                }
                else bad_input = 0;
            }
            return 0;
        }
    }
    else { // 无索引输入
        map<string, vector<string>> :: iterator maps = index_exp.begin();
        for(; maps != index_exp.end(); ++maps) {
            cout << '[' << maps -> first << ']';
            vector<string> exps = maps -> second;
            sort(exps.begin(), exps.end());
            vector<string> :: iterator itexp = exps.begin();
            for(; itexp != exps.end(); ++itexp) {
                ss.clear();
                ss.str(*itexp + ";");
                ts.Clear_buffer();
                //cout << "the flow is " << ss.str() << '\n';
                
                double ans;
                try{
                    ans = expression();
                }
                catch (runtime_error& e) {
                    bad_input = 1;
                    //cout << e.what() << endl;
                }
                if(!bad_input) {
                    cout << '\n' << *itexp << '=' << ans;
                }
                else bad_input = 0;
            }
            if(maps != --index_exp.end()) {
                cout << '\n';
            }
        }
        return 0;
    }
    return 0;
}

catch (runtime_error& e) {
    cout << e.what() << endl;
    //keep_window_open("~~");
    return 1;
}
catch (...) {
    cout << "exception \n";
    //keep_window_open("~~");
    return 2;
}

//------------------------------------------------------------------------------