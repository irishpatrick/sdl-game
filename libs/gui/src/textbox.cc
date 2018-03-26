#include "textbox.h"

namespace gui {

TextBox::TextBox() : Widget() {
    len = 0;
    c_time = 0;
    rate = 0;
    currentChar = 0;
    running = true;
    visible = false;
}

TextBox::~TextBox() {

}

void TextBox::pushLine(const string& str) {
    queue.push_back(str);
}

void TextBox::step() {
    currentChar = 0;
    len = queue[0].size();
    queue.erase(queue.begin());
    running = true;
}

void TextBox::update(float delta) {
    if (queue.size() == 0) {
        visible = false;
    } else {
        visible = true;
    }

    if (!visible || !running) {
        return;
    }

    if (c_time >= rate) {
        c_time = 0;
        currentChar++;
        if (currentChar == len) {
            running = false;
        }
    }

    c_time += delta;
}

void TextBox::draw(SDL_Renderer* renderer) {

}

}
