#pragma once

#include "core_api.hpp"

#include <string>
#include <sstream>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>
#include "BoundingBox.hpp"
//#include <spdlog/spdlog.h>
//#include <spdlog/sinks/basic_file_sink.h>

namespace engine {

class Sprite;
class Group;

class Util
{
public:
    //CORE_API static uint32_t getNow();
	CORE_API static std::string checkCollision(Sprite*, Sprite*);
	CORE_API static std::string checkVelocityCollision(Sprite*, Sprite*, float);
	CORE_API static void contain(Sprite*, Sprite*);
	CORE_API static BoundingBox getAABB(Sprite*, uint32_t);
	CORE_API static std::string RectToString(SDL_Rect*);
	CORE_API static bool JsonExists(nlohmann::json&, const std::string&);
	CORE_API static std::vector<Sprite*> GetCollisions(Sprite*, Group*);
	CORE_API static std::vector<Sprite*> getVelocityCollisions(Sprite*, Group*, float);
	CORE_API static std::vector<Sprite*> getVelocityCollisions(Sprite*, std::vector<Sprite*>&, float);
	CORE_API static float lerp(float, float, float);
	CORE_API static void formatPath(std::string&);
	//CORE_API static void initSpdlog();

	CORE_API static const int UP = 0;
	CORE_API static const int DOWN = 1;
	CORE_API static const int LEFT = 2;
	CORE_API static const int RIGHT = 3;
	CORE_API static const int NO_COLLISION = 4;

};

}
