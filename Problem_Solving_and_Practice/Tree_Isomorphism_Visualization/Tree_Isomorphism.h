#ifndef TREE_ISOMORPHISM_H_INCLUDED
#define TREE_ISOMORPHISM_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>
#include <time.h>
#include <sstream>
#include <map>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/fl_draw.H>

using namespace std;

struct param;


struct node {
    string parent;
    vector<string> children;
    string symbol = ""; // the code if this node is root
    int child_symbol = 0;
    node() {
        parent = "";
        children.clear();
        symbol = "";
        child_symbol = 0;
    }
    node(string p, string c) {
        parent = p;
        if(c != "") children.push_back(c);
        symbol = "";
        child_symbol = 0;
    }
    node & operator=(const node& tmp) {
        this -> parent = tmp.parent;
        this -> children.clear();
        for(int i = 0; i < tmp.children.size(); ++i) {
            this -> children.push_back(tmp.children[i]);
        }
        this -> symbol = tmp.symbol;
        this -> child_symbol = tmp.child_symbol;
        return *this;
    }
};

// The class of tree
class Tree {
    private:
    bool isTree;
    string root;
    map<string, node> all_nodes; // store the information of name-parent and children
    map<string, string> isomor_node; // store the consistent nodes between two isomorphism trees
    map<string, Fl_Button *> draw_nodes;
    map<string, param> parameters;
    int r;
    int len;
    public:
    Tree() {
        isTree = true;
        root = "";
        all_nodes.clear();
        isomor_node.clear();
        draw_nodes.clear();
        r = 40;
        len = 80;
        parameters.clear();
    }
    Tree(string file);
    bool isTreeLegal();
    void GetTreeCode();
    bool isIsomorphism(Tree & t);
    void DrawTree(int ct_x, int ct_y, Tree * t, int length, int height);
    void DrawNode(int ct_x, int ct_y, string name, Tree * t, int length, int height); // length ang height include button
    void GetConsistentNodes(string node_one, string node_two, Tree & t); // node_one and node_two are the consistent nodes between two trees
    void PrintInfo() {
        map<string, node>::iterator it = all_nodes.begin();
        for(int i = 0; i < all_nodes.size(); ++i) {
            cout << "node name: " << it->first << " and node code: " << it->second.symbol << endl;
            ++it;
        }
    }
    template<class T>
    void ChangeNodeColor(string name, T color) {
        Fl_Button * node = draw_nodes[name];
        node->color(color);
        node->redraw();
    }
    ~Tree() {
        if(isTree) {
            map<string, Fl_Button *>::iterator it = draw_nodes.begin();
            for(int i = 0; i < all_nodes.size(); ++i) {
                delete it -> second;
                ++it;
            }
        }
    }
};

class Line:public Fl_Widget {
   private:
   int bx;
   int by;
   int ex;
   int ey;
   char * label;
   public:
   Line(int x, int y, int x1, int y1):Fl_Widget(x, y, x1, y1) {
      bx = x;
      by = y;
      ex = x1;
      ey = y1;
   }

   void draw() {
      fl_begin_line();
      fl_color(FL_BLACK);
      fl_line(bx, by, ex,ey);
      fl_end_line();
   }

};

struct param {
    string name;
    Tree * another_tree;
    param(string n, Tree * t):name(n), another_tree(t) {}
    param & operator=(const param& tmp) {
        this -> name = tmp.name;
        this -> another_tree = tmp.another_tree;
        return *this;
    }
    param() {
        name = "";
        another_tree = NULL;
    }
};

#endif // TREE_ISOMORPHISM_H_INCLUDED