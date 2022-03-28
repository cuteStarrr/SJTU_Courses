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

string SortChildren(string oldtree, int start, int end) {
    if((oldtree[start] != '1') || (oldtree[end] != '0')) {cout << '@' << '\n'; throw oldtree;}
    if(end == start + 1) return "" + oldtree[start] + oldtree[end];

    int ones = 0;
    int zeros = 0;
    vector<string> children;
    int last = start + 1;
    for(int i = last; i <= end - 1; ++i) {
        if(oldtree[i] == '1') ++ones;
        else ++zeros;
        if(ones == zeros) {
            string str = oldtree.substr(last, i + 1 - last);
            str = SortChildren(str, 0, i - last);
            children.push_back(str);
            ones = 0;
            zeros = 0;
            last = i + 1;
        }
    }
    if(ones != zeros) {cout << '#' << '\n'; throw oldtree;}

    sort(children.rbegin(), children.rend());
    string newtree = "1";
    for(vector<string>::iterator iter = children.begin(); iter != children.end(); ++iter) {
        newtree += *iter;
    }

    return newtree + "0";

}

string GetCode(string oldtree) {
    return SortChildren(oldtree, 0, oldtree.size() - 1);
}

int main() {
    string tree1_old;
    string tree2_old;
    string tree1_new;
    string tree2_new;
    string illegal_tree = "";
    string output = "";
    int in_char = 1;

    tree1_old = "11011000";
    tree2_old = "11100100";
    in_char += tree1_old.size() + tree2_old.size();

    try {
        tree1_new = GetCode(tree1_old);
        cout << "tree1_new: " << tree1_new << '\n';
    }
    catch(string tree) {
        illegal_tree += " " + tree;
    }
    try {
        tree2_new = GetCode(tree2_old);
        cout << "tree2_new: " << tree2_new << '\n';
    }
    catch(string tree) {
        illegal_tree += " " + tree;
    }

    if(illegal_tree.size() != 0) {
        output = "Invalid tree(s):" + illegal_tree;
    }
    else {
        if(tree1_new == tree2_new) {
            output = tree1_old + " and " + tree2_old + " are isomorphic";
        }
        else {
            output = tree1_old + " and " + tree2_old + " are non-isomorphic";
        }
    }

    cout << in_char << ':' << output.size() << '\n';
    cout << output;

    return 0;
}