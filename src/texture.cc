#include "texture.h"

Texture::Texture()
{

}

Texture::Texture(SDL_Renderer* r)
{
    w = 0;
    h = 0;
    tex = NULL;
    renderer = r;
    surf = NULL;
    ready = false;
}

Texture::~Texture()
{

}

uint32_t Texture::getW()
{
    return w;
}

uint32_t Texture::getH()
{
    return h;
}

void Texture::set(SDL_Surface* s)
{
    surf = s;
    w = surf->w;
    h = surf->h;
	//printf("%d, %d\n", w, h);
    ready = true;
}

void Texture::create(SDL_Renderer* r)
{
    tex = SDL_CreateTextureFromSurface(r, surf);
}

SDL_Texture* Texture::use()
{
    if (ready && tex == NULL)
    {
        //printf("creating texture\n");
        tex = SDL_CreateTextureFromSurface(renderer, surf);
    }
    return tex;
}

void Texture::destroy()
{
    SDL_DestroyTexture(tex);
}
