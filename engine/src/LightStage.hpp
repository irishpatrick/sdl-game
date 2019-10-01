#pragma once

#include "Light.hpp"
#include "Sprite.hpp"
#include "Context.hpp"
#include "Canvas.hpp"
#include <vector>

namespace engine
{
    class LightStage : public Sprite
    {
    public:
        LightStage();
        ~LightStage();

        void init(Context&);
        void addLight(Light*);
        void draw(Context&, float);

    private:
        std::vector<Light*> lights;
        Canvas clear;
    };
}