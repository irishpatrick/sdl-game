#include "widget.h"

namespace gui {

Widget::Widget() {
    x = 0;
    y = 0;
    visible = false;
}

Widget::~Widget() {

}

void Widget::setVisible(bool v) {
    visible = v;
}

void Widget::draw(SDL_Renderer* renderer) {

}

}
