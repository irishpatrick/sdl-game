#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>

class Text
{
public:
    Text();
    ~Text();

    void draw(SDL_Renderer*);
    void destroy();

private:
    TTF_Font* font_;
    SDL_Color color_;
    SDL_Surface* surface_;
    SDL_Texture* texture_;
};

#endif /* TEXT_H */
