#ifndef GUI_LIST_H
#define GUI_LIST_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include "cairo.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "widget.h"

using namespace std;

namespace gui {

class List : public Widget {

public:
    List();
    ~List();

    void draw(SDL_Renderer*) override;
    void setFont(SDL_Renderer*, const string&);
    void addItem(const string&);
    void setCurrent(unsigned int);

private:
    vector<string> items;
    map<char, SDL_Texture*> font;
    int font_w;
    int font_h;
    float padding;
    unsigned int current;

    SDL_Texture* background;
};

}

#endif /* GUI_LIST_H */
