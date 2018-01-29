#include "text.h"

Text::Text()
{
    font_ = TTF_OpenFont("Sans.ttf", 24);
    color_ = {255, 255, 255};
}

Text::~Text()
{

}

void Text::draw(SDL_Renderer* r)
{

}

void Text::destroy()
{
    if (surface_ != nullptr)
    {
        SDL_FreeSurface(surface_);
    }
    if (texture_ != nullptr)
    {
        SDL_DestroyTexture(texture_);
    }
}
