#pragma once

#include <vector>
#include <string>
#include "Rect.hpp"

namespace engine
{
    class Animation
    {
    public:
        Animation();
        ~Animation();

        void play();
        void stop();
        void update();
        void setCurrentFrame(int);

        void setFps(int);
        void setTicksPerSecond(int);
        void pushFrame(Rect);

        Rect getCurrentFrame();

        std::string toString();

    private:
        int fps;
        int currentFrame;
        int ticks;
        int ticksPerSecond;
        bool running;
        std::vector<Rect> frames;
        std::vector<int*> animations;
    };
}
