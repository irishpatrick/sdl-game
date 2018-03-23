#ifndef GUI_TREE_H
#define GUI_TREE_H

#include <string>
#include <map>
#include "SDL2/SDL.h"
#include "widget.h"

using namespace std;

namespace gui {

class Tree {

public:
    Tree();
    ~Tree();

private:
    Widget* current;
    map<string, Widget*> tree;
};

}

#endif /* GUI_TREE_H */
