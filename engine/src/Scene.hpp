#pragma once

#include "Context.hpp"
#include "Sprite.hpp"
#include <vector>

namespace engine
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

        void init(Context&);
        void update(float);
        void draw(Context&);

        void addSprite(Sprite&);

    private:
        std::vector<Sprite> sprites;
    };
}