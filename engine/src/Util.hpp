#pragma once

#include "core_api.hpp"

#include <string>
#include <sstream>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <nlohmann/json.hpp>
#include "BoundingBox.hpp"
#include <experimental/filesystem>

namespace engine {

class Sprite;
class Group;

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;

class Util
{
public:
	CORE_API static bool simpleCollision(Sprite*, Sprite*);
	CORE_API static std::string checkCollision(Sprite*, Sprite*);
    CORE_API static bool checkIntersect(BoundingBox*, BoundingBox*);
    CORE_API static bool checkIntersect(BoundingBox, BoundingBox);
    CORE_API static bool checkVelocityIntersect(BoundingBox&, Point&, BoundingBox&, Point&);
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
	CORE_API static json loadJson(const std::string&);
    CORE_API static float getSign(float);

	CORE_API static const int UP = 0;
	CORE_API static const int DOWN = 1;
	CORE_API static const int LEFT = 2;
	CORE_API static const int RIGHT = 3;
	CORE_API static const int NO_COLLISION = 4;

};

}
