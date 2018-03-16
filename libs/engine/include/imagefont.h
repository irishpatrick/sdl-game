#ifndef IMAGEFONT_H
#define IMAGEFONT_H

#include <map>
#include <cstdint>
#include "SDL2/SDL.h"

using namespace std;

namespace engine {

class Texture;

class ImageFont
{
public:
    ImageFont();
    ~ImageFont();

    void setCharSize(uint32_t, uint32_t);
    void setTexture(Texture*);

private:
    Texture* tex;
    uint32_t w;
    uint32_t h;
    map<char, SDL_Rect> charMap;
};

}

#endif /* IMAGEFONT_H */
