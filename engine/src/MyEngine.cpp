#include "MyEngine.hpp"
#include "Sprite.hpp"

namespace engine
{
    std::vector<Sprite*> MyEngine::sprites = std::vector<Sprite*>();

    void MyEngine::addSprite(Sprite* s)
    {
        sprites.push_back(s);
    }

    void MyEngine::delSprite(Sprite* s)
    {
        auto it = sprites.end();
        while (it != sprites.begin())
        {
            if (s->getUUID() == (*it)->getUUID())
            {
                sprites.erase(it);
            }
            --it;
        }
    }
}