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

}
