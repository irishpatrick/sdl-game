#pragma once

#include <vector>

namespace engine
{
    typedef struct _AnimFrame
    {
        int x;
        int y;
        int w;
        int h;
    } AnimFrame;

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
        void pushFrame(AnimFrame);
        void createAnimation(const std::string&, int*, int, int);

    private:
        int fps;
        int currentFrame;
        int ticks;
        int ticksPerSecond;
        bool running;
        std::vector<AnimFrame> frames;
        std::vector<int*> animations;
    };
}
