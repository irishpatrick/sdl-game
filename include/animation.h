#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <json.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include "texture.h"
#include "assets.h"

class Animation
{
public:
    Animation();
    ~Animation();

    void InitFromJson(const std::string&);
    SDL_Rect* GetCurrentFrame();

private:
    std::map<std::string, uint32_t*> animmap_;
    SDL_Rect* currentframe;
    std::vector<SDL_Rect> frames_;
    Texture* tex_;
};

#endif /* ANIMATION_H */