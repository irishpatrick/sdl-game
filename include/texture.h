#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdio>
#include <SDL.h>

class Texture
{
public:
    Texture();
    Texture(SDL_Renderer*);
    ~Texture();

    void set(SDL_Surface*);
    void create(SDL_Renderer*);
    int getW();
    int getH();
    SDL_Texture* use();
    void destroy();

    bool ready;

private:
    int w;
    int h;
    SDL_Texture* tex;
    SDL_Surface* surf;
    SDL_Renderer* renderer;
};

#endif /* TEXTURE_H */