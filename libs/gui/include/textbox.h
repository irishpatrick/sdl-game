#ifndef GUI_TEXTBOX_H
#define GUI_TEXTBOX_H

#include <string>
#include <vector>
#include <iostream>
#include "cairo.h"
#include "SDL2/SDL.h"
#include "widget.h"

using namespace std;

namespace gui {

class TextBox : public Widget {

public:
    TextBox();
    ~TextBox();

    void pushLine(const string&);
    void step();
    void update(float);
    void draw(SDL_Renderer*);

private:
    vector<string> queue;
    unsigned int currentChar;
    unsigned int len;
    float c_time;
    float rate;
    bool running;

};

}

#endif /* GUI_TEXTBOX_H */
