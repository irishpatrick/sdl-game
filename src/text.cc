#include "text.h"
#include "timer.h"

Text::Text(const std::string& str)
{
    redraw_ = false;
    timer_ = new Timer();
    font_ = TTF_OpenFont("Sans.ttf", 24);
    color_ = {255, 255, 255};
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    depth_ = 1;
    text_ = str;

    buffer_ = (char*)malloc(text_.size());
}

Text::~Text()
{
    delete timer_;
    if (surface_ != nullptr)
    {
        SDL_FreeSurface(surface_);
    }
    if (texture_ != nullptr)
    {
        SDL_DestroyTexture(texture_);
    }
    free(buffer_);
}

void Text::reset()
{
    
}

void Text::update()
{
    if (timer_->Tick())
    {
        if (depth_ > text_.size())
        {
            return;
        }
        redraw_ = true;
        strncpy(buffer_, text_.c_str(), depth_);
        depth_++;
    }
}

void Text::draw(SDL_Renderer* r)
{
    if (redraw_)
    {
        redraw_ = false;
        texture_ = SDL_CreateTextureFromSurface(r, surface_);
    }

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(r, texture_, nullptr, &rect);
}
