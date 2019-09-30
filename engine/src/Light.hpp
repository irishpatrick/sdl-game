#pragma once

#include "Sprite.hpp"
#include "Context.hpp"

namespace engine
{
    class Light : public Sprite
    {
    public:
        Light();
        ~Light();

        void draw(Context&, float);
    };
}