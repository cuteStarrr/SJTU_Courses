#include "Tree_Isomorphism.h"

//------------------------------------------------------------------------------

int main()
{
    int win_length = 1800;
    int win_height = 800;
    Fl_Window win(win_length, win_height, "Tree Isomorphism");

    Tree tree1("1-1.txt");
    Tree tree2("1-2.txt");

    if(!(tree1.isTreeLegal() && tree2.isTreeLegal())) {
        cout << "Illegal Tree!" << endl;
        return 0;
    }

    cout << "legal trees!" << endl;

    tree1.GetTreeCode();
    tree2.GetTreeCode();

    cout << "get codes!" << endl;

    //tree1.PrintInfo();
    //tree2.PrintInfo();

    if(tree1.isIsomorphism(tree2)) {
        cout << "start drawing!" << endl;
        win.begin();
        tree1.DrawTree(int(win_length / 4), int(win_height / 8), &tree2, int(win_length / 2), int(win_height / 8));
        tree2.DrawTree(int(win_length * 3 / 4), int(win_height / 8), &tree1, int(win_length / 2), int(win_height / 8));
        cout << "finish drawing!" << endl;
        win.end();
        win.show();
        return Fl::run();
    }
    else {
        cout << "The two trees are not isomorphic!" << endl;
        return 0;
    }
}

//------------------------------------------------------------------------------