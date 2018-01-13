#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <string>
#include <json.hpp>
#include "texture.h"

class Animation
{
public:
    Animation();
    ~Animation();

    void initfromjson(const std::string& fn)
    {

    }

private:
    std::vector<SDL_Rect> frames_;
    Texture* tex_;
};

#endif /* ANIMATION_H */