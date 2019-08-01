#pragma once

#include "Sprite.hpp"
#include "Canvas.hpp"
#include "Context.hpp"

namespace engine
{
    class Debugger : public Sprite
    {
    public:
        Debugger() : Sprite()
        {}

        ~Debugger()
        {}

        void init(Context&);
        void update(float);
        Canvas* getCanvas();

    private:
        Canvas canvas;
    };
}