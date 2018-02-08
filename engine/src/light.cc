#include "light.h"
#include "texture.h"
#include "group.h"

Light::Light()
{
    x = 0;
    y = 0;
    size = 0;
}

Light::~Light()
{

}

void Light::settexture(Texture* t)
{
    texture_ = t;
}

void Light::querytexture()
{
    SDL_SetTextureBlendMode(texture_->use(), SDL_BLENDMODE_ADD);
}

void Light::draw(SDL_Renderer* r)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = size;
    rect.h = size;
    SDL_RenderCopy(r, texture_->use(), nullptr, &rect);
}