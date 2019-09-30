#pragma once

#include "Sprite.hpp"
#include "Context.hpp"
#include "Color.hpp"

namespace engine
{
    class Light : public Sprite
    {
    public:
        Light();
        ~Light();

        void setIntensity(double);
        void draw(Context&, float);

        Color color;

    private:
        double intensity;
        double temperature;
    };
}