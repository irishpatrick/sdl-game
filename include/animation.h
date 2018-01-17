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
#include <cstring>
#include "texture.h"
#include "assets.h"
#include "timer.h"

typedef struct FrameSet_
{
    char* name;
    uint32_t fps;
    uint32_t* frames;
} FrameSet;

class Animation
{
public:
    Animation();
    ~Animation();

    void InitFromJson(const std::string&);
    void Start(const std::string&, bool);
    void Stop();
    SDL_Rect* GetCurrentFrame();

private:
    //std::map<std::string, FrameSet> animmap_;
    std::vector<FrameSet*> animations_;
    SDL_Rect* currentframe;
    FrameSet* currentset_;
    std::vector<SDL_Rect*> frames_;
    Texture* tex_;
    Timer timer_;
};

#endif /* ANIMATION_H */