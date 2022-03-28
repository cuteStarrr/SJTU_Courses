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

struct HuffNode {
    int left_child = 0;
    int right_child = 0;
    int parent = 0;
    string symbol = "";
    int freq = 0;
    string huffcode = "";
};

class HuffTree {
    private:
    HuffNode * root = NULL;
    int symbol_num = 0;

    public:
    map<string, string> code;
    HuffTree() : root(NULL), symbol_num(0) {}
    HuffTree(map<string, int> ele_fre);
    void HuffCode();
    string Print(); // return the number of output char of codes
    ~HuffTree() {delete [] root;}
};

HuffTree :: HuffTree(map<string, int> ele_fre) {
    root = new HuffNode[ele_fre.size() * 2];
    symbol_num = ele_fre.size();

    /* initialize the leaf */
    map<string, int> :: iterator it = ele_fre.begin();
    for(int i = 0; i < symbol_num; ++i) {
        root[i + symbol_num].symbol = it -> first;
        root[i + symbol_num].freq = it -> second;
        root[i + symbol_num].left_child = 0;
        root[i + symbol_num].right_child = 0;
        root[i + symbol_num].huffcode = "";
        root[i + symbol_num].parent = 0;
        ++it;
    }

    int min1,min2,pos_min1,pos_min2;
    for(int times = symbol_num - 1; times > 0; --times) {
        min1 = min2 = 1000;
        pos_min1 = pos_min2 = 0;
        for(int range = times + 1; range < 2 * symbol_num; ++range) {
            if(! root[range].parent) {
                if((root[range].freq < min1) || (root[range].freq == min1 && root[range].symbol < root[pos_min1].symbol)) {
                    min2 = min1;
                    min1 = root[range].freq;
                    pos_min2 = pos_min1;
                    pos_min1 = range;
                }
                else {
                    if((root[range].freq < min2) || (root[range].freq == min2 && root[range].symbol < root[pos_min2].symbol)) {
                        min2 = root[range].freq;
                        pos_min2 = range;
                    }
                }
            }
        }
        root[pos_min1].parent = times;
        root[pos_min2].parent = times;
        root[times].freq = min1 + min2;
        root[times].huffcode = "";
        root[times].left_child = pos_min1;
        root[times].right_child = pos_min2;
        root[times].symbol = root[pos_min1].symbol + root[pos_min2].symbol;
        root[times].parent = 0;
    }
}

void HuffTree :: HuffCode() {
    int parent, child;
    for(int times = symbol_num; times < 2 * symbol_num; ++times) {
        parent = root[times].parent;
        child = times;
        while(parent) {
            if(root[parent].left_child == child) {
                root[times].huffcode = "0" + root[times].huffcode;
            }
            else root[times].huffcode = "1" + root[times].huffcode;
            child = parent;
            parent = root[child].parent;
        }
        code.insert(pair<string, string> (root[times].symbol, root[times].huffcode));
    }
}

string HuffTree :: Print() {
    string output = "";
    for(map<string, string> :: iterator it = code.begin(); it != code.end(); ++it) {
        output = output + '\n' + it -> first + " " + it -> second;
    }
    return output;
}

void GetFrequency(string str, map<string, int> & ele_fre) {
    for(auto s : str) {
        string cur(1,s);
        map<string, int> :: iterator it = ele_fre.find(cur);
        if (ele_fre.end() == it) {
            ele_fre.insert(pair<string, int> (cur, 1));
        }
        else {
            ++ it -> second;
        }
    }
    return ;
}

string GetInput(int & num) {
    string str;
    string input = "";
    while(getline(cin,str)) {
        input = input + str;
        ++num;
    }
    --num; // last line no '\n'
    num += input.size();

    return input;
}


int main() {
    int in_char = 0;
    string input;
    map<string, int> frequency;
    
    input = GetInput(in_char);

    GetFrequency(input, frequency);

    HuffTree hufftree(frequency);

    hufftree.HuffCode();

    string output = hufftree.Print();
    
    int out_text = 0;
    map<string, int> :: iterator times = frequency.begin();
    for(map<string, string> :: iterator it = hufftree.code.begin(); it != hufftree.code.end(); ++it) {
        out_text += times -> second * it -> second.size();
        ++times;
    }
    output = to_string(out_text) + output;
    
    cout << in_char << ':' << output.size() << '\n';
    cout << output;

    return 0;
}