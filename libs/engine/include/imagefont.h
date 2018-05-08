#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <SDL2/SDL.h>

using namespace std;

namespace engine {

class Texture;

class ImageFont
{
public:
    ImageFont();
    ~ImageFont();

    void setScale(float);
    void setTexture(Texture*);
    void buildMap(uint32_t, uint32_t);
    void renderChar(const string&, float, float, SDL_Renderer*);
    void renderString(const string&, float, float, SDL_Renderer*);

private:
    Texture* tex;
    uint32_t w;
    uint32_t h;
    float scale;
    SDL_Rect* crects;
    const std::string charMap = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
};

}
