#include "imagefont.h"

namespace gui {

ImageFont::ImageFont() {
    scale = 0.2;
}

ImageFont::~ImageFont() {

}

void ImageFont::setScale(double s) {
    scale = s;
}

void ImageFont::setFont(SDL_Renderer* renderer, const string& dir) {
    for (char i=32; i<123; i++) {
        string fn = dir + "/" + i + ".png";
        font[i] = IMG_LoadTexture(renderer, fn.c_str());
        if (font[i] == nullptr) {
            cout << "IMG_LoadTexture error: " << IMG_GetError() << endl;
        }
        SDL_QueryTexture(font['a'], nullptr, nullptr, &font_w, &font_h);

        //scale
        font_w = font_w * scale;
        font_h = font_h * scale;
    }
}

void ImageFont::drawChar(SDL_Renderer* renderer, char c, float x, float y) {
    SDL_Texture* tex = getChar(c);
    if (tex == nullptr) {
        cout << "bad texture" << endl;
        return;
    }
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = font_w;
    r.h = font_h;

    SDL_RenderCopy(renderer, tex, nullptr, &r);
}

SDL_Texture* ImageFont::getChar(char c) {
    if (font.find(c) != font.end()) {
        return font[c];
    }
    cout << "char not found!" << endl;
    return nullptr;
}

int ImageFont::getFontWidth() {
    return font_w;
}

int ImageFont::getFontHeight() {
    return font_h;
}

int ImageFont::getScaleWidth() {
    return font_w * scale;
}

int ImageFont::getScaleHeight() {
    return font_h * scale;
}

}
