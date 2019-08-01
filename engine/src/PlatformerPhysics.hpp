#pragma once

#include "Group.hpp"
#include "Sprite.hpp"

namespace engine
{
    class PlatformerPhysics
    {
    public:
        static void resolveCollision(Sprite&, Sprite&, float);
    };
}