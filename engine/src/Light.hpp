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
        void setObeyCamera(bool);
        void draw(Context&, float) override;

        Color color;

    private:
        bool obeyCamera;
        double intensity;
        double temperature;
    };
}