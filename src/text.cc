#include "text.h"
#include "timer.h"

Text::Text(): Text("")
{

}

Text::Text(const std::string& str)
{
    redraw_ = false;
    surface_ = nullptr;
    texture_ = nullptr;
    timer_ = new Timer();
    font_ = TTF_OpenFont("../assets/fonts/IndieFlower-Regular.ttf", 400);
    if (font_ == nullptr)
    {
        std::cout << "font error: " << TTF_GetError() << std::endl;
    }
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
    printf("destroyed text!\n");
}

void Text::setText(const std::string& str)
{
    free(buffer_);
    text_ = str;
    buffer_ = (char*)malloc(text_.size());
}

void Text::setSpeed(double a)
{
    timer_->SetInterval(a);
}

void Text::reset()
{
    free(buffer_);
    buffer_ = (char*)malloc(text_.size());
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
        SDL_FreeSurface(surface_);
        SDL_DestroyTexture(texture_);
        surface_ = TTF_RenderText_Solid(font_, buffer_, color_);
        texture_ = SDL_CreateTextureFromSurface(r, surface_);
    }

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(r, texture_, nullptr, &rect);
}

void Text::staticDraw(SDL_Renderer* r)
{
    //std::cout << "staticDraw" << std::endl;
    SDL_FreeSurface(surface_);
    SDL_DestroyTexture(texture_);
    surface_ = TTF_RenderText_Solid(font_, text_.c_str(), color_);
    texture_ = SDL_CreateTextureFromSurface(r, surface_);
    w = 300;
    h = 100;

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(r, texture_, nullptr, &rect);
}
