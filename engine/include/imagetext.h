#ifndef IMAGETEXT_H
#define IMAGETEXT_H

#include <string>
#include <map>
#include <cstring>
#include <cstdlib>
#include <SDL2/SDL.h>

#include "entity.h"

class Texture;

class ImageText: public Entity
{
public:
    ImageText();
    ImageText(const std::string&);
    ~ImageText();

private:
    std::string text;
    Texture* font;
    std::map<char, SDL_Rect> charmap;
};

#endif /* IMAGETEXT_H */
