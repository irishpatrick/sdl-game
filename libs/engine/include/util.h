#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <vector>
#include "boost/lexical_cast.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "nlohmann/json.hpp"

namespace engine {

class Sprite;
class Group;

enum Direction {NORTH, EAST, SOUTH, WEST, NONE};

class Util
{
public:
    //static uint32_t getNow();
    static SDL_Texture* loadTexture(const std::string&, SDL_Renderer*);
    static std::string checkCollision(Sprite*, Sprite*);
    static std::string checkVelocityCollision(Sprite*, Sprite*, float);
    static void contain(Sprite*, Sprite*);
    static SDL_Rect getAABB(Sprite*, uint32_t);
    static std::string RectToString(SDL_Rect*);
    static bool JsonExists(nlohmann::json&, const std::string&);
    static std::vector<Sprite*> GetCollisions(Sprite*, Group*);
    static std::vector<Sprite*> getVelocityCollisions(Sprite*, Group*, float);
};

}

#endif /* UTIL_H */
