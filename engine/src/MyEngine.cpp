#include "MyEngine.hpp"
#include "Sprite.hpp"
#include "State.hpp"
#include <iostream>

namespace engine
{
    std::vector<Sprite*> MyEngine::sprites;
    std::vector<State*> MyEngine::states;
    State* MyEngine::currentState = nullptr;
    Context MyEngine::ctx;
    Camera MyEngine::camera;

    void MyEngine::printNum()
    {
        std::cout << "sprites: " << sprites.size() << std::endl;
    }

    void MyEngine::addSprite(Sprite* s)
    {
        if (s == nullptr)
        {
            return;
        }
        sprites.push_back(s);

        printNum();
    }

    void MyEngine::delSprite(Sprite* s)
    {
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

        printNum();
    }

    void MyEngine::addState(State* s)
    {
        if (s == nullptr)
        {
            return;
        }
        states.push_back(s);
    }

    void MyEngine::delState(State* s)
    {
        if (s == nullptr)
        {
            return;
        }
        delState(s->getName());
    }

    void MyEngine::delState(const std::string& name)
    {
        auto it = states.end();
        while (it != states.begin())
        {
            if (*it != nullptr && name == (*it)->getName())
            {
                states.erase(it);
            }
            --it;
        }
    }

    State* MyEngine::getState(const std::string& name)
    {
        for (auto& e : states)
        {
            if (e->getName() == name)
            {
                return e;
            }
        }
        return nullptr;
    }

    void MyEngine::setCurrentState(const std::string& name)
    {
        int found = 0;
        for (auto& e : states)
        {
            if (e != nullptr && e->getName() == name)
            {
                found = 1;
                currentState = e;
            }
        }
        if (!found)
        {
            std::cout << "error: state not found" << std::endl;
        }
    }

    State* MyEngine::getCurrentState()
    {
        return currentState;
    }

    Context& MyEngine::getContext()
    {
        return ctx;
    }

    /*Sprite* MyEngine::newSprite()
    {
        
    }*/
}