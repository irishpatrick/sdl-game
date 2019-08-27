#include "Animation.hpp"
#include <iostream>
#include <sstream>

namespace engine
{
    Animation::Animation() :
        fps(0),
        currentFrame(0),
        ticks(0),
        ticksPerSecond(83),
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
        currentFrame = (currentFrame + (int)passed) % frames.size();
        ++ticks; // increment ticks
        if (second > 1.0f)
        {
            //std::cout << "tick" << std::endl;
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

    void Animation::setFps(int val)
    {
        fps = val;
    }

    void Animation::setTicksPerSecond(int val)
    {
        ticksPerSecond = val;
    }

    Rect Animation::getCurrentFrame()
    {
        return frames[currentFrame];
    }

    std::string rectToString(Rect* r)
    {
        std::stringstream ss;
        ss << "[" << r->x << "," << r->y << "," << r->w << "," << r->h << "]";
        return ss.str();
    }

    std::string Animation::toString()
    {
        std::stringstream ss;
        ss << "Animation {" << fps << "," << frames.size();
        for (auto& e : frames)
        {
            ss << "," << rectToString(&e);
        }
        ss << "}";

        return ss.str();
    }
}
