#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <cstdlib>
#include <cstdio>

#include <rapidjson/document.h>
#include <string>
#include <fstream>
#include <streambuf>
#include "assets.h"
class Sprite;
#include "sprite.h"
class Camera;
#include "camera.h"

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
    void setassets(Assets*);

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
    Assets* assets_;
    std::vector<Sprite*> renderList;
    Camera* camera;
};

#endif /* GROUP_H */