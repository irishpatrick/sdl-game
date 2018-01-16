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
#include "timer.h"

typedef struct FrameSet_
{
    std::string name;
    uint32_t fps;
    uint32_t* frames;
} FrameSet;

class Animation
{
public:
    Animation();
    ~Animation();

    void InitFromJson(const std::string&);
    void Start(const std::string&, bool loop);
    void Stop();
    SDL_Rect* GetCurrentFrame();

private:
    std::map<std::string, uint32_t*> animmap_;
    SDL_Rect* currentframe;
    std::vector<SDL_Rect> frames_;
    std::vector<uint32_t> rates_;
    Texture* tex_;
    Timer timer_;
};

#endif /* ANIMATION_H */