#include "imagefont.hpp"
#include "texture.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>

namespace engine {

ImageFont::ImageFont() {
    w = 0;
    h = 0;
    maskR = 0;
    maskG = 0;
    maskB = 0;
    isMaskSet = false;
    scale = 1.0f;
    tex = nullptr;
    crects = (SDL_Rect*)malloc(63 * sizeof(SDL_Rect));
}

ImageFont::~ImageFont() {
	free(crects);
}

void ImageFont::setColor(uint8_t r, uint8_t g, uint8_t b) {
    maskR = r;
    maskG = g;
    maskB = b;
    isMaskSet = false;
}

void ImageFont::setColor(Color& c) {
	maskR = c.getChannel(Color::RED);
	maskG = c.getChannel(Color::GREEN);
	maskB = c.getChannel(Color::BLUE);
	isMaskSet = false;
}

void ImageFont::setScale(float s) {
    scale = s;
}

void ImageFont::setTexture(Texture* t) {
    tex = t;
	w = ceil((double)tex->getW() / 63.0) + 3;
	h = tex->getH();
	std::cout << "setting dimensions to " << w << ", " << h << std::endl;
}

void ImageFont::buildMap() {
    std::cout << "building map...";
    for (int i=0; i<63; i++) {
        crects[i].x = i * w;
        crects[i].y = 0;
        crects[i].w = w;
        crects[i].h = h;
    }
    std::cout << "ok" << std::endl;
}

void ImageFont::renderChar(const std::string& c, float x, float y, SDL_Renderer* r) {
    size_t found = charMap.find(c);
    if (found == std::string::npos) {
        //cout << "unknown char!" << endl;
        return;
    }

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = (uint32_t) (w * scale);
    dst.h = (uint32_t) (h * scale);

    SDL_Rect* src = &crects[found];
    if (!isMaskSet) {
        SDL_SetTextureColorMod(tex->use(), maskR, maskG, maskB);
    }
    SDL_RenderCopy(r, tex->use(), src, &dst);
}

void ImageFont::renderString(const std::string& str, float ox, float oy, SDL_Renderer* r) {
    float x = ox;
    float y = oy;
    //std::cout << "renderString() " << str << std::endl;
    for (uint32_t i=0; i<str.length(); i++) {
        char c = str[i];
        std::string s;
        std::stringstream ss;
        ss << c;
        std::getline(ss, s);
        renderChar(s, x + (i * w * scale), y, r);
    }
}

}
