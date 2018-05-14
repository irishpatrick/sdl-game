#pragma once

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cmath>

#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

namespace engine {

class Texture;
class Timer;

typedef struct {
    char* name;
    uint32_t fps;
    uint32_t count;
    uint32_t* frames;
} FrameSet;

class Animation
{
public:
    Animation();
    ~Animation();

    void InitFromJson(const std::string&);
    void Start(const std::string&, bool);
    void Update();
    void Stop();
    void Kill();
    SDL_Rect* GetCurrentFrame();
    Texture* GetTexture();
    uint32_t GetFrameWidth();
    uint32_t GetFrameHeight();

private:
    //std::map<std::string, FrameSet> animmap_;
    std::vector<FrameSet*> animations_;
    SDL_Rect* currentframe_;
    uint32_t currentindex_;
    FrameSet* currentset_;
    std::vector<SDL_Rect*> frames_;
    Texture* tex_;
    Timer* timer_;
    bool running_;
    bool looping_;
    uint32_t framewidth_;
    uint32_t frameheight_;
};

}
