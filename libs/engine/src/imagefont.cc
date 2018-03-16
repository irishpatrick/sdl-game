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

}
