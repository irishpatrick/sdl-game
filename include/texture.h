#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdio>
#include <cstdint>
#include <SDL.h>

class Texture
{
public:
    Texture();
    Texture(SDL_Renderer*);
    ~Texture();

    void set(SDL_Surface*);
    void create(SDL_Renderer*);
    uint32_t getW();
    uint32_t getH();
    SDL_Texture* use();
    void destroy();

    bool ready;

private:
    uint32_t w;
    uint32_t h;
    SDL_Texture* tex;
    SDL_Surface* surf;
    SDL_Renderer* renderer;
};

#endif /* TEXTURE_H */