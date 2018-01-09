#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

#include "line.h"

class Sprite;
#include "sprite.h"

class Util
{
public:
    Util();
    ~Util();

    //static uint32_t getNow();
    static SDL_Texture* loadTexture(const std::string&, SDL_Renderer*);
    static std::string checkCollision(Sprite*, Sprite*);
    static void contain(Sprite*, Sprite*);
    static SDL_Rect getAABB(Sprite*, uint32_t);
};

#endif /* UTIL_H */