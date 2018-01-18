#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <boost/lexical_cast.hpp>

class Sprite;

class Util
{
public:
    //static uint32_t getNow();
    static SDL_Texture* loadTexture(const std::string&, SDL_Renderer*);
    static std::string checkCollision(Sprite*, Sprite*);
    static void contain(Sprite*, Sprite*);
    static SDL_Rect getAABB(Sprite*, uint32_t);
    static std::string RectToString(SDL_Rect*);
};

#endif /* UTIL_H */