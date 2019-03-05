#include "Canvas.hpp"

namespace engine
{
    void Canvas::create(Context& ctx, uint32_t w, uint32_t h)
    {
        surface = SDL_CreateRGBSurface
        (
            0, w, h, 32,
            0x00ff0000,
            0x0000ff00,
            0x000000ff,
            0
        );

        texture = SDL_CreateTextureFromSurface(ctx.getRenderer(), surface);
    }
}