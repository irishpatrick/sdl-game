#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include "SDL2/SDL.h"

namespace gui {

class Widget {

public:
    Widget();
    virtual ~Widget();

    void setVisible(bool);
    virtual void draw(SDL_Renderer*);

    float x;
    float y;

protected:
    int w;
    int h;
    bool visible;

};

}

#endif /* GUI_WIDGET_H */
