/*
This file is used to read from a txt file and contruct a tree in the form of vector composed of nodes.
It is encapsulated as a class.
*/
#include "Tree_Isomorphism.h"


void node_cb(Fl_Widget* o, void* data) {
   Fl_Button* node_one=(Fl_Button*)o;
   param new_data = *(param *) data;
   static Fl_Color ori_color= node_one->color();
   static int light_color = 213;
   if(node_one->color() == light_color) {
       node_one->color(ori_color);
       (new_data.another_tree)->ChangeNodeColor(new_data.name, ori_color);
   }
   else {
      node_one->color(light_color);
      (new_data.another_tree)->ChangeNodeColor(new_data.name, light_color);
   }
   node_one->redraw();
}

// draw itself and children line
// remember to control range
void Tree::DrawNode(int ct_x, int ct_y, string name, Tree * t, int length, int height) {
    //cout << "start drawing child node" << endl;
    Fl_Button * draw_node = new Fl_Button(ct_x - r / 2, ct_y - r / 2, r, r, t->isomor_node[isomor_node[name]].c_str());
    param data(isomor_node[name], t);
    parameters.insert(pair<string, param> (name, data));
    draw_node -> callback(node_cb, (void *)&(parameters[name]));
    draw_nodes[name] = draw_node;
    //cout << "finish drawing child node" << endl;

    if(all_nodes[name].children.size() == 0) {
        return ;
    }

    int n = all_nodes[name].children.size();
    int small_length = length / n;
    int start = ct_x - length / 2 + small_length / 2;
    for(int i = 0; i < n; ++i) {
        int next_ctx = start + i * small_length;
        int next_cty = ct_y + height;
        //cout << "start drawing line" << endl;
        Line * connection = new Line(ct_x, ct_y + r / 2, next_ctx, next_cty - r / 2);
        //cout << "finish drawing line" << endl;
        DrawNode(next_ctx, next_cty, all_nodes[name].children[i], t, small_length, height);
    }
}

// draw a tree from top and down
void Tree::DrawTree(int ct_x, int ct_y, Tree * t, int length, int height) {
    int lt_x = ct_x - r / 2;
    int lt_y = ct_y - r / 2;

    //cout << "draw root node" << endl;
    Fl_Button * new_node = new Fl_Button (lt_x, lt_y, r, r, root.c_str());
    param data(isomor_node[root], t);
    parameters.insert(pair<string, param> (root, data));
    new_node -> callback(node_cb, (void *)&(parameters[root]));
    draw_nodes[root] = new_node;
    //cout << "finish drawing root node" << endl;

    int n = all_nodes[root].children.size();
    int small_length = length / n;
    int start = ct_x - length / 2 + small_length / 2;
    for(int i = 0; i < n; ++i) {
        int next_ctx = start + i * small_length;
        int next_cty = ct_y + height;
        Line * connection = new Line(ct_x, ct_y + r / 2, next_ctx, next_cty - r / 2);
        DrawNode(next_ctx, next_cty, all_nodes[root].children[i], t, small_length, height);
    }
}

void Tree::GetConsistentNodes(string node_one, string node_two, Tree & t) {
    isomor_node[node_one] = node_two;
    t.isomor_node[node_two] = node_one;
    //cout << "get consistent nodes self" << endl;
    if(all_nodes[node_one].children.size() == 0) {return ;}
    for(int i = 0; i < all_nodes[node_one].child_symbol; ++i) {
        for(int j = 0; j < t.all_nodes[node_two].child_symbol; ++j) {
            string child_one = all_nodes[node_one].children[i];
            string child_two = t.all_nodes[node_two].children[j];
            if(all_nodes[child_one].symbol == t.all_nodes[child_two].symbol) {
                GetConsistentNodes(child_one, child_two, t);
                break;
            }
        }
    }
}


bool Tree::isIsomorphism(Tree & t) {
    if(all_nodes[root].symbol != t.all_nodes[t.root].symbol) return false;
    else {
        // find out the consistent nodes between two trees
        GetConsistentNodes(root, t.root, t);
        //cout << "finish isomorphism" << endl;
        return true;
    }
}


// Get the code of a tree with fixed root

void Tree::GetTreeCode() {
    int fixed_symbol = 0;
    map<string, node>::iterator it;
    for(it = all_nodes.begin(); it != all_nodes.end(); ++it) {
        if(it -> second.children.size() == 0) {
            it -> second.symbol = "01";
            ++all_nodes[it -> second.parent].child_symbol;
            ++fixed_symbol;
        }
    }
    //cout << "finish giving codes to leaves!" << endl;
    while(fixed_symbol != all_nodes.size()) {
        for(it = all_nodes.begin(); it != all_nodes.end(); ++it) {
            if(it -> second.child_symbol == it -> second.children.size()) {
                if(it -> second.symbol == "") { // don't regard the leaves, because it is handled just before
                    vector<string> c_symbols;
                    for(int i = 0; i < it -> second.children.size(); ++i) {
                        c_symbols.push_back(all_nodes[it -> second.children[i]].symbol);
                    }
                    sort(c_symbols.begin(), c_symbols.end());
                    it -> second.symbol = it -> second.symbol + "0";
                    for(int i = 0; i < c_symbols.size(); ++i) {
                        it -> second.symbol = it -> second.symbol + c_symbols[i];
                    }
                    it -> second.symbol = it -> second.symbol + "1";
                    if(it -> second.parent != "")
                        ++all_nodes[it -> second.parent].child_symbol;
                    ++fixed_symbol;
                    //cout << "the number of nodes is: " << all_nodes.size() << " and the number of assigned nodes is: " << fixed_symbol << endl;
                }
            }
        }
    }
}

// Figure out legality and the root node
bool Tree::isTreeLegal() {
    if(!isTree) return false;

    int num_root = 0;
    string r_node = "";
    map<string, node>::iterator it;
    for(it = all_nodes.begin(); it != all_nodes.end(); ++it) {
        if(it -> second.parent == "") {
            if(num_root == 0) {
                ++ num_root;
                r_node = it -> first;
            }
            else {
                isTree = false;
                return false;
            }
        }
    }

    if(num_root == 0) {
        isTree = false;
        return false;
    }

    root = r_node;
    return isTree;
}

Tree::Tree(string file) {
    isTree = true;
    root = "";
    all_nodes.clear();
    isomor_node.clear();
    draw_nodes.clear();
    r = 40;
    len = 80;
    parameters.clear();

    ifstream fp;
    fp.open(file, ios::in);

    if(!fp.is_open()) {
        cout << "Read error!";
        isTree = false;
        return ;
    }

    string line;
    while(getline(fp, line)) {
        if(!line.empty()) {
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); // delete space
            //cout << "the line is: " << line << endl;
            if(line.find("->") == string::npos) {
                cout << "No -> in the line!";
                isTree = false;
                fp.close();
                return ;
            }
            else {
                line.replace(line.find("->"), 2, " ");
                string p, c;
                stringstream ss(line);
                ss >> p >> c;
                if(p == "" || c == "") {
                    cout << "there is an empty node!" << endl;
                    isTree = false;
                    fp.close();
                    return ;
                }
                if(all_nodes.find(p) == all_nodes.end()) { // there is no key of p
                    all_nodes[p] = node("", c);
                }
                else {
                    if(find(all_nodes[p].children.begin(), all_nodes[p].children.end(), c) == all_nodes[p].children.end())
                        all_nodes[p].children.push_back(c);
                }
                if(all_nodes.find(c) == all_nodes.end()) { // there is no key of c
                    all_nodes[c] = node(p, "");
                }
                else {
                    if(all_nodes[c].parent == "") {
                        all_nodes[c].parent = p;
                    }
                    else {
                        if(all_nodes[c].parent != p) {
                            cout << "node " << c << " has two different parents!" << endl;
                            isTree = false;
                            fp.close();
                            return ;
                        }
                    }
                }
            }
        }
    }
    fp.close();
}
