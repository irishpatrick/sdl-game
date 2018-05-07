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

    void setCharSize(uint32_t, uint32_t);
    void setScale(float);
    void setTexture(Texture*);
    void buildMap();
    void renderChar(char, float, float, SDL_Renderer*);
    void renderString(const string&, float, float, SDL_Renderer*);

private:
    Texture* tex;
    uint32_t w;
    uint32_t h;
    float scale;
    map<char, SDL_Rect> charMap;
    SDL_Rect* crects;
};

}
