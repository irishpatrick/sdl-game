#pragma once

#include <vector>

namespace engine
{
    class Sprite;
    
    class MyEngine
    {
    public:
        static void addSprite(Sprite*);
        static void delSprite(Sprite*);

    private:
        static std::vector<Sprite*> sprites;
    };
}