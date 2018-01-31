#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <SDL.h>
#include <SDL_ttf.h>

class Timer;

class Text
{
public:
    Text();
    Text(const std::string&);
    ~Text();

    void update();
    void draw(SDL_Renderer*);
    void reset();
    void setText(const std::string&);

    float x;
    float y;
    uint32_t w;
    uint32_t h;

private:
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

#endif /* TEXT_H */
