#ifndef TITLESCREENSTATE_HPP
#define TITLESCREENSTATE_HPP

#include "engine.hpp"

using namespace engine;

class TitleScreenState : public State
{
public:
    TitleScreenState();
    virtual void init(Context&);
    virtual void update(float);
    virtual void render(Context&, float);

private:
    Sprite bg;
};

#endif /* TITLESCREENSTATE_HPP */