#include "imagefont.h"
#include "texture.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

namespace engine {

ImageFont::ImageFont() {
    w = 0;
    h = 0;
    scale = 1.0f;
    tex = nullptr;
    crects = nullptr;
}

ImageFont::~ImageFont() {
    if (crects != nullptr) {
        free(crects);
    } else {
        cout << "crects var was nullptr" << endl;
    }
}

void ImageFont::setScale(float s) {
    scale = s;
}

void ImageFont::setTexture(Texture* t) {
    tex = t;
}

void ImageFont::buildMap(uint32_t a, uint32_t b) {
    w = a;
    h = b;
    cout << "building map...";
    crects = (SDL_Rect*)malloc(63 * sizeof(SDL_Rect));
    for (int i=0; i<63; i++) {
        crects[i].x = i * w;
        crects[i].y = 0;
        crects[i].w = w;
        crects[i].h = h;
    }
    cout << "ok" << endl;
}

void ImageFont::renderChar(const string& c, float x, float y, SDL_Renderer* r) {
    size_t found = charMap.find(c);
    if (found == string::npos) {
        //cout << "unknown char!" << endl;
        return;
    }

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = (uint32_t) (w * scale);
    dst.h = (uint32_t) (h * scale);

    SDL_Rect* src = &crects[found];

    SDL_RenderCopy(r, tex->use(), src, &dst);
}

void ImageFont::renderString(const string& str, float ox, float oy, SDL_Renderer* r) {
    float x = ox;
    float y = oy;
    for (uint32_t i=0; i<str.length(); i++) {
        char c = str[i];
        string s;
        stringstream ss;
        ss << c;
        getline(ss, s);
        renderChar(s, x + (i * w * scale), y, r);
    }
}

}
