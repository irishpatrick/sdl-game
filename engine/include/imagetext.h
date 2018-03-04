#ifndef IMAGETEXT_H
#define IMAGETEXT_H

#include <string>
#include <cstring>
#include <cstdlib>
#include "SDL.h"
#include "engine.h"

#include "entity.h"

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
