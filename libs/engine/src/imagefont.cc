#include "imagefont.h"
#include "texture.h"
#include <iostream>
#include <cstdlib>

namespace engine {

ImageFont::ImageFont() {
    w = 0;
    h = 0;
    scale = 1.0f;
    tex = nullptr;
    crects = (SDL_Rect*)malloc(58 * sizeof(SDL_Rect));
}

ImageFont::~ImageFont() {
    free(crects);
}

void ImageFont::setCharSize(uint32_t a, uint32_t b) {
    w = a;
    h = b;
}

void ImageFont::setScale(float s) {
    scale = s;
}

void ImageFont::setTexture(Texture* t) {
    tex = t;
}

void ImageFont::buildMap() {
    cout << "building map...";
    for (uint8_t i=32; i<128; i++) {
        crects[i].x = (i - 32) * w;
        crects[i].y = 0;
        crects[i].w = w;
        crects[i].h = h;
    }
    cout << "ok" << endl;
}

void ImageFont::renderChar(char c, float x, float y, SDL_Renderer* r) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = (uint32_t) (w * scale);
    dst.h = (uint32_t) (h * scale);

    SDL_Rect* src = &charMap[c];
    cout << "src " << src->x << "," << src->y << "," << src->w << "," << src->h << endl;
    cout << "dst " << dst.x << "," << dst.y << "," << dst.w << "," << dst.h << endl;

    SDL_RenderCopy(r, tex->use(), &charMap[c], &dst);
}

void ImageFont::renderString(const string& str, float ox, float oy, SDL_Renderer* r) {
    float x = ox;
    float y = oy;
    cout << "renderString() " << str << endl;
    for (uint32_t i=0; i<str.length(); i++) {
        char c = str[i];
        renderChar(c, x + (i * w * scale), y, r);
    }
    cout << endl;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 60;
    rect.h = 60;
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = w;
    src.h = h;
    SDL_RenderCopy(r, tex->use(), &src, &rect);
}

}
