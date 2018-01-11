#ifndef LIGHT_H
#define LIGHT_H

#include <SDL.h>
#include "texture.h"
#include "group.h"

class Light
{
public:
    Light();
    ~Light();

    void settexture(Texture*);
    void setparent(Group*);
    void querytexture();
    void draw(SDL_Renderer*);

    float x;
    float y;
    float size;

private:
    Texture* texture_;
    Group* parent;
};

#endif /* LIGHT_H */