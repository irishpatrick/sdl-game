#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <cstdint>
#include <SDL.h>
#include <SDL_image.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>


class Group;
#include "group.h"
#include "texture.h"

class Sprite
{
public:
    Sprite();
    virtual ~Sprite();

    virtual void setTexture(Texture*);
    virtual void loadTexture(const std::string&, SDL_Renderer*);
    virtual void draw(SDL_Renderer*);
    virtual void update(float);
	void queryTexture();
    inline void pos(float a, float b)
    {
        x = a;
        y = b;
    }
    virtual void setParent(Group*);
    virtual Group* getParent();

    virtual const std::string getUUID();

    float x;
    float y;
    float xvel;
    float yvel;
    float speed;
    int w;
    int h;
    Texture* texture;
    bool solid;
    bool dynamic;
    std::string name;
protected:
    Group* parent;

private:
    boost::uuids::uuid tag;
};

#endif /* SPRITE_H */