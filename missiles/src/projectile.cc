#include "projectile.h"

Projectile::Projectile()
{
    vx = 0;
    vy = 0;
    angle = 0;
    thrust = 0;
    camera = nullptr;
}

Projectile::~Projectile()
{

}

void Projectile::setCamera(Camera* c)
{
    camera = c;
}

void Projectile::update(float delta)
{
    x += xvel * delta;
    y += yvel * delta;
}

void Projectile::draw(SDL_Renderer* r)
{
    if (!visible_) return;
    //printf("%x\n", texture->use());

    //printf("%d, %d\n", w, h);
    SDL_Rect rect;
    if (camera != nullptr)
    {
        rect.x = x + camera->x;
        rect.y = y + camera->y;
    }
    else
    {
        rect.x = x;
        rect.y = y;
    }
    rect.w = w;
    rect.h = h;

    SDL_Point center = {rect.w / 2, rect.h / 2};
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
