#pragma once

namespace engine
{
    class vec2
    {
    public:
        vec2();
        ~vec2();

        static vec2 add(vec2, vec2);
        static vec2 scale(vec2, float);
        static float dot(vec2, vec2);

        float x;
        float y;
    };
}