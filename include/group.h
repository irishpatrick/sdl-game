#ifndef GROUP_H
#define GROUP_H

#include <SDL.h>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <rapidjson/document.h>
#include <string>
#include <fstream>
#include <streambuf>

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

#endif /* GROUP_H */