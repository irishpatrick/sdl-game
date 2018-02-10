#include "plane.h"

Plane::Plane()
{
    vx = 0;
    vy = 0;
    angle = 0;
}

Plane::~Plane()
{

}

void Plane::draw(SDL_Renderer* r)
{
    if (!visible_) return;
    //printf("%x\n", texture->use());

    //printf("%d, %d\n", w, h);
    SDL_Rect rect;
    if (parent != NULL)
    {
        rect.x = x + parent->screenX();
        rect.y = y + parent->screenY();
    }
    else
    {
        rect.x = x;
        rect.y = y;
    }
    rect.w = w;
    rect.h = h;

    SDL_Point center = {rect.x + (rect.w / 2), rect.y + (rect.h / 2)};
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    //if (texture->use() == nullptr) return;
    if (anim->GetTexture() != nullptr)
    {
        SDL_RenderCopy(r, texture->use(), anim->GetCurrentFrame(), &rect);
    }
    else
    {
        SDL_RenderCopyEx(r, texture->use(), NULL, &rect, (double)angle, &center, flip);
    }
}
