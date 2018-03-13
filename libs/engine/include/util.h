#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>

namespace engine {

class Sprite;
class Group;

class Util
{
public:
    //static uint32_t getNow();
    static SDL_Texture* loadTexture(const std::string&, SDL_Renderer*);
    static std::string checkCollision(Sprite*, Sprite*);
    static void contain(Sprite*, Sprite*);
    static SDL_Rect getAABB(Sprite*, uint32_t);
    static std::string RectToString(SDL_Rect*);
    static bool JsonExists(nlohmann::json&, const std::string&);
    static std::vector<Sprite*> GetCollisions(Sprite*, Group*);
};

}

#endif /* UTIL_H */
