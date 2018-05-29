#pragma once

#include "core_api.hpp"

#include <string>
#include <sstream>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>

namespace engine {

class Sprite;
class Group;

enum Direction {NORTH, EAST, SOUTH, WEST, NONE};

class Util
{
public:
    //CORE_API static uint32_t getNow();
	CORE_API static SDL_Texture* loadTexture(const std::string&, SDL_Renderer*);
	CORE_API static std::string checkCollision(Sprite*, Sprite*);
	CORE_API static std::string checkVelocityCollision(Sprite*, Sprite*, float);
	CORE_API static void contain(Sprite*, Sprite*);
	CORE_API static SDL_Rect getAABB(Sprite*, uint32_t);
	CORE_API static std::string RectToString(SDL_Rect*);
	CORE_API static bool JsonExists(nlohmann::json&, const std::string&);
	CORE_API static std::vector<Sprite*> GetCollisions(Sprite*, Group*);
	CORE_API static std::vector<Sprite*> getVelocityCollisions(Sprite*, Group*, float);
	CORE_API static int initSDL(SDL_Window**, SDL_Renderer**, const std::string&, int, int, bool);
	CORE_API static float lerp(float, float, float);
};

}
