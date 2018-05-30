#pragma once

#include "core_api.hpp"

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <streambuf>

#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

namespace engine {

class Sprite;
class Camera;

class Group
{
public:
	CORE_API Group();
	CORE_API ~Group();

	CORE_API void init(SDL_Renderer*);
	CORE_API void init_from_json(const std::string&);
	CORE_API void update(float);
	CORE_API void draw(SDL_Renderer*);
	CORE_API void destroy();
	CORE_API std::vector<Sprite*> getSprites();
	CORE_API void add(Sprite*);
	CORE_API void queryAll();
	CORE_API void sort();
	CORE_API Sprite* get_sprite_by_name(const std::string&);
	CORE_API Sprite* getSpriteAtLocation(float, float);

    template <class T>
    void getSpritesByType(std::vector<T*>&);

	CORE_API void remove(Sprite*);

	CORE_API void setCamera(Camera*);

	CORE_API float screenX();
    CORE_API float screenY();

    float x;
    float y;
    float sx;
    float sy;

    bool dynamic;
private:
    std::vector<Sprite*> renderList;
    Camera* camera;
};

}

#include "group.inl"
