#pragma once

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
    Group();
    ~Group();

    void init(SDL_Renderer*);
	void init_from_json(const std::string&);
    void update(float);
    void draw(SDL_Renderer*);
    void destroy();
    std::vector<Sprite*> getSprites();
    void add(Sprite*);
	void queryAll();
    void sort();
    Sprite* get_sprite_by_name(const std::string&);
    Sprite* getSpriteAtLocation(float, float);

    template <class T>
    void getSpritesByType(std::vector<T*>&);

	void remove(Sprite*);

    void setCamera(Camera*);

    float screenX();
    float screenY();

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

#include "group.tpp"