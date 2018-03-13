#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "entity.h"

namespace engine {

class Timer;

class Text: public Entity
{
public:
    Text();
    Text(const std::string&);
    ~Text();

    void update();
    void draw(SDL_Renderer*);
    void staticDraw(SDL_Renderer*);
    void reset();
    void setText(const std::string&);
    void setSpeed(double);
    void setSize(uint32_t);

private:
    uint32_t size_;
    std::string text_;
    uint32_t depth_;
    char* buffer_;
    Timer* timer_;
    bool redraw_;
    TTF_Font* font_;
    SDL_Color color_;
    SDL_Surface* surface_;
    SDL_Texture* texture_;
};

}

#endif /* TEXT_H */
