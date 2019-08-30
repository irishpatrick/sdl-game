#pragma once

namespace engine
{
    union Color_Value
    {
        int i;
        float f;
        char c;
    };
    struct Color_RGB
    {
        Color_Value r;
        Color_Value g;
        Color_Value b;
    };
    struct Color_HSL
    {
        Color_Value h;
        Color_Value s;
        Color_Value l;
    };
    struct Color_HSV
    {
        Color_Value h;
        Color_Value s;
        Color_Value v;
    };
    class Color
    {
    public:
        Color();
        ~Color();

        Color_RGB getRGB();
        Color_HSL getHSL();
        Color_HSV getHSV();

    private:
    };
}