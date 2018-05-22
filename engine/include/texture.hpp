#pragma once

#include <cstdio>
#include <cstdint>
#include <string>
#include <SDL2/SDL.h>

namespace engine {

class Texture
{
public:
    Texture();
    Texture(SDL_Renderer*);
    ~Texture();

    void set(SDL_Surface*);
    void copy(Texture*);
    void create(SDL_Renderer*);
    uint32_t getW();
    uint32_t getH();
    SDL_Texture* use();
    void destroy();

    inline std::string getName() {
        return name_;
    }

    bool ready;

private:
    uint32_t w;
    uint32_t h;
    std::string name_;
    SDL_Texture* tex;
    SDL_Surface* surf;
    SDL_Renderer* renderer;
};

}
