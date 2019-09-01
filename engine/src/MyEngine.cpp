#include "MyEngine.hpp"
#include "Sprite.hpp"

namespace engine
{
    std::vector<Sprite*> MyEngine::sprites = std::vector<Sprite*>();

    void MyEngine::addSprite(Sprite* s)
    {
        if (s == nullptr)
        {
            return;
        }
        sprites.push_back(s);
    }

    void MyEngine::delSprite(Sprite* s)
    {
        return;
        if (s == nullptr)
        {
            return;
        }
        auto it = sprites.end();
        while (it != sprites.begin())
        {
            if (*it != nullptr && s->getUUID() == (*it)->getUUID())
            {
                sprites.erase(it);
            }
            --it;
        }
    }
}