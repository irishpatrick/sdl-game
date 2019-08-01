#include "Debugger.hpp"

namespace engine
{
    void Debugger::init(Context& ctx)
    {
        canvas.create(ctx, texture, w, h);
    }

    void Debugger::update(float delta)
    {
        canvas.update();
    }

    Canvas* Debugger::getCanvas()
    {
        return &canvas;
    }
}