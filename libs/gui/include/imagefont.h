#ifndef GUI_IMAGEFONT_H
#define GUI_IMAGEFONT_H

#include <iostream>
#include <map>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

namespace gui {

class ImageFont {

public:
    ImageFont();
    ~ImageFont();

    void setScale(double);
    void setFont(SDL_Renderer*, const string&);
    void drawChar(SDL_Renderer*, char, float, float);

    SDL_Texture* getChar(char);
    int getFontWidth();
    int getFontHeight();
    int getScaleWidth();
    int getScaleHeight();

private:
    map<char, SDL_Texture*> font;
    int font_w;
    int font_h;
    double scale;

};

}

#endif /* GUI_IMAGEFONT_H */
