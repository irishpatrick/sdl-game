#include "Color.hpp"

namespace engine
{
    Color::Color()
    {

    }

    Color::~Color()
    {

    }

    void Color::setRGB(double r, double g, double b)
    {
        rgb.r.f = r;
        rgb.g.f = g;
        rgb.b.f = b;
    }

    Color_RGB Color::getRGB()
    {
        return rgb;
    }

    Color_HSL Color::getHSL()
    {
        Color_HSL out;

        return out;
    }

    Color_HSV Color::getHSV()
    {
        Color_HSV out;

        return out;
    }
}