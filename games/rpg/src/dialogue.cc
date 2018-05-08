#include "dialogue.h"
#include <SDL2/SDL.h>

#define MAXLEN 24

// method to pop front of vector
template<typename T>
void pop_front(std::vector<T>& v) {
    assert(!v.empty());
    v.erase(v.begin());
}

Dialogue::Dialogue() {
    visible = true;
    width = 0;
    height = 0;
    x = 0.0f;
    y = 0.0f;
}

Dialogue::~Dialogue() {

}

void Dialogue::initFont(engine::Texture* t) {
    font.setTexture(t);
    font.buildMap(202, 201);
    font.setScale(0.055f);
}

void Dialogue::push(const std::string& str) {
    if (stack.empty()) {
        visible = true;
    }
    if (str.size() < MAXLEN) {
        stack.push_back(str);
    } else {
        int len = str.size();
        int lines = len / MAXLEN;
        int extra = len % MAXLEN;
        std::cout << "len: " << len << std::endl;
        std::cout << "lines: " << lines << std::endl;
        std::cout << "extra: " << extra << std::endl;
        for (int i=0; i<lines; i++) {
            std::cout << "loop from " << i*MAXLEN << " to " << (i+1)*MAXLEN << std::endl;
            stack.push_back(str.substr(i*MAXLEN, MAXLEN));
        }
        stack.push_back(str.substr(lines*MAXLEN, lines*MAXLEN+extra));
    }
}

void Dialogue::pop() {
    pop_front(stack);
    if (stack.empty()) {
        visible = false;
    }
}

void Dialogue::render(engine::Context* ctx) {
    if (!visible) {
        return;
    }

    SDL_Rect box[2];
    SDL_Rect* bg = &box[0];
    SDL_Rect* fg = &box[1];

    float cx = ctx->coordX(0.0f) - (width / 2.0f);
    float cy = ctx->coordY(0.75) - (height / 2.0f);

    bg->x = cx;
    bg->y = cy;
    bg->w = width;
    bg->h = height;

    fg->x = cx + 1;
    fg->y = cy + 1;
    fg->w = width - 2;
    fg->h = height - 2;

    // background
    SDL_SetRenderDrawColor(ctx->getRenderer(), 0x00, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(ctx->getRenderer(), bg);

    // foreground
    SDL_SetRenderDrawColor(ctx->getRenderer(), 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(ctx->getRenderer(), fg);

    // text
    SDL_SetRenderDrawColor(ctx->getRenderer(), 0x00, 0x00, 0x00, 0xff);
    font.renderString(stack[0], cx + 10, cy + 10, ctx->getRenderer());
}
