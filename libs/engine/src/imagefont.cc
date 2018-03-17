#include "imagefont.h"
#include "texture.h"

namespace engine {

ImageFont::ImageFont() {
    w = 0;
    h = 0;
    tex = nullptr;
}

ImageFont::~ImageFont() {

}

void ImageFont::setCharSize(uint32_t a, uint32_t b) {
    w = a;
    h = b;
}

void ImageFont::setTexture(Texture* t) {
    tex = t;
}

void ImageFont::buildMap() {
    for (int i=32; i<128; i++) {
        SDL_Rect* r = &charMap[i];
        r->x = (i - 32) * w;
        r->y = 0;
        r->w = w;
        r->h = h;
    }
}

void ImageFont::renderChar(char c, float x, float y, SDL_Renderer* r) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(r, tex->use(), &charMap[c], &dst);
}

void ImageFont::renderString(const string& str, float ox, float oy, SDL_Renderer* r) {
    float x = ox;
    float y = oy;
    for (uint32_t i=0; i<str.length(); i++) {
        char c = str[i];
        renderChar(c, x + (i * w), y, r);
    }
}

}
