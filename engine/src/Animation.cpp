#include "Animation.hpp"
#include <iostream>

namespace engine
{
    Animation::Animation() :
        fps(0),
        currentFrame(0),
        ticks(0),
        ticksPerSecond(0),
        running(0)
    {

    }

    Animation::~Animation()
    {

    }

    void Animation::play()
    {
        running = 1;
        currentFrame = 0;
    }

    void Animation::stop()
    {
        running = 0;
    }

    void Animation::update()
    {
        if (!running)
        {
            return;
        }

        float second = (float)ticks / (float)ticksPerSecond;
        float passed = second * (float)fps;
        currentFrame = currentFrame + (int)passed;
        ++ticks; // increment ticks
        if (second > 1.0f)
        {
            ticks = 0;
        }
    }

    void Animation::setCurrentFrame(int frame)
    {
        currentFrame = frame;
    }

    void Animation::pushFrame(Rect frame)
    {
        frames.push_back(frame);
    }

    void Animation::createAnimation(const std::string& name, int* frames, int numframes, int fps)
    {

    }

    void Animation::setFps(int val)
    {
        fps = val;
    }

    void Animation::setTicksPerSecond(int val)
    {
        ticksPerSecond = val;
    }
}
